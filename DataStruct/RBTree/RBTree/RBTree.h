#pragma once
#include<iostream>
using namespace std;
// 红黑树
// 红黑树特点：查找速度快，数据量越大，速度越快
// 变色：红色，黑色  旋转：平衡因子  普通操作  O(logn)时间内做查找，插入和删除
// map ,set 都是基于rbtree

// 定义一个枚举类 限制颜色类型
enum COLOR { RED, BLACK };

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode(const K& key, const V& value)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)
	{}

	RBTreeNode* _pLeft;
	RBTreeNode* _pRight;
	RBTreeNode* _pParent;
	K _key;
	V _value;
	COLOR _color;
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	// 构造
	RBTree()
		:_pRoot(NULL)
	{}

	// 插入 是一个关键函数
	bool Insert(const K& key, const V& value)
	{
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
			_pRoot->_color = BLACK;
			return true;
		}
		// 下面开始寻找点，分情况
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else
				return false;
		}
		// 找到点pParent保存, 创建一个待插入的节点
		pCur = new Node(key, value);
		if (key < pParent->_key)
		{
			pParent->_pLeft = pCur;
		}
		if (key > pParent->_key)
		{
			pParent->_pRight = pCur;
		}
		// 把父亲指针先指上去
		pCur->_pParent = pParent;
		// 考虑变色问题
		while (pParent->_color == RED && _pRoot != pCur)
		{
			Node* pGrandFather = pParent->_pParent;
			if (pGrandFather->_pLeft == pParent)
			{
				// 跟父亲同级的节点，且是爷爷节点的右节点
				Node* pUncle = pGrandFather->_pRight;
				if (pUncle&&RED == pUncle->_color)//情况三
				{
					pParent->_color = BLACK;
					pUncle->_color = BLACK;
					pGrandFather->_color = RED;

					pCur = pGrandFather;
					pParent = pParent->_pParent;
				}

				else//情况五
				{
					if (pCur == pParent->_pRight)
					{
						_RotateL(pParent);
						std::swap(pCur, pParent);
					}
					// 爷爷变红色了，就不能是root了，将父亲节点变黑，爷爷节点左旋
					pGrandFather->_color = RED;
					pParent->_color = BLACK;
					_RotateR(pGrandFather);
				}

			}

			else
			{
				// 假如 父亲位子和 叔叔位子对换
				Node* pUncle = pGrandFather->_pLeft;
				if (pUncle && RED == pUncle->_color)//情况三
				{
					pParent->_color = BLACK;
					pUncle->_color = BLACK;
					pGrandFather->_color = RED;

					pCur = pGrandFather;
					pParent = pParent->_pParent;
				}

				else//情况五
				{
					if (pCur == pParent->_pLeft)
					{
						_RotateR(pParent);
						std::swap(pCur, pParent);
					}
					// 爷爷变红色了，就不能是root了，将父亲节点变黑，爷爷节点左旋
					pGrandFather->_color = RED;
					pParent->_color = BLACK;
					_RotateL(pGrandFather);
				}

			}
		}
		_pRoot->_color = BLACK;
		return true;
	}

	/*
	左旋，1首先保存他的右节点 2 再保存右节点的左节点
	旋转时候 右节点成为根节点，右节点的左节点连接到 原来根节点的右节点
	注意判断一下 原本root的节点是不是真的root,或许也有parent,
	如果没有 直接生成新的，假如有，则判断一下root是parent的left还是right
	连接就可以了
	*/
	// 左右旋转
	void _RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		else
		{
			pSubR->_pLeft = pParent;
			Node* pPParent = pParent->_pParent;

			pParent->_pParent = pSubR;
			pSubR->_pParent = pPParent;
			if (NULL == pPParent)
				_pRoot = pSubR;
			else
			{
				if (pPParent->_pLeft = pParent)
					pPParent->_pLeft = pSubR;
				else
					pPParent->_pRight = pSubR;
			}
		}
	}

	void _RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
		{
			pSubLR->_pParent = pParent;
		}
		else
		{
			pSubL->_pRight = pParent;
			Node* pPParent = pParent->_pParent;
			pParent->_pParent = pSubL;
			pSubL->_pParent = pPParent;
			if (NULL == pParent->_pParent)
			{
				_pRoot = pSubL;
			}
			else
			{
				if (pPParent->_pLeft == pParent)
					pPParent->_pLeft = pSubL;
				else
					pPParent->_pRight = pSubL;
			}
		}
	}

	// 检测是否符合红黑树 
	bool CheckRBTree()
	{
		size_t k = 0;
		if (NULL == _pRoot)
			return true;
		if (_pRoot->_color == RED)
		{
			cout << "根节点为红" << " ";
			return false;
		}

		size_t BlackCount = 0;
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
			{
				BlackCount++;
			}
			pCur = pCur->_pLeft;
		}
		return _CheckRBTree(_pRoot, BlackCount, k);
	}

	void MidOrder()
	{
		cout << "MidOrder: ";
		_MidOrder(_pRoot);
		cout << endl;
	}

private:
	void _MidOrder(Node *root)
	{
		if (root == nullptr) return;
		cout << root->_key << " ";
		_MidOrder(root->_pLeft);
		_MidOrder(root->_pRight);
	}

	bool _CheckRBTree(Node* pRoot, const size_t BlackCount, size_t k)
	{
		if (NULL == pRoot)
			return true;
		if (BLACK == pRoot->_color)
			k++;
		Node* pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "相邻为红" << " ";
			return false;
		}

		if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
		{
			if (k != BlackCount)
			{
				cout << "黑色个数不相等" << " ";
				return false;
			}
		}

		return _CheckRBTree(pRoot->_pLeft, BlackCount, k) && _CheckRBTree(pRoot->_pRight, BlackCount, k);
	}

protected:
	Node* _pRoot;
};
