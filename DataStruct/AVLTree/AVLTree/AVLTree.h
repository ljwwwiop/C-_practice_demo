#pragma once
// 实现平衡二叉树
#include <iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value) :_key(key), _value(value), _left(nullptr), _right(nullptr), _parent(nullptr)
	{};
	AVLTreeNode<K, V> *_left;
	AVLTreeNode<K, V> *_right;
	AVLTreeNode<K, V> *_parent;
	K _key;
	V _value;
	// bf 平衡因子，进行旋转使用 ，0 1 -1 ，2 
	int _bf;
};

template<class K,class V>
class AVLTree 
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree() :_root(nullptr) {}
	// 插入操作
	// 首先 1 判断值 2 寻找到父节点将待插入节点连接进去 3 将后面的节点连到插入的节点上面了   
	bool Insert(const K &key, const V &value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, value);
			return true;
		}
		Node *pCur = _root;
		Node *pParent = nullptr;

		while (pCur)
		{
			// 当小于root.val 在 左子树
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_left;
			}
			else if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_right;
			}
			else
			{
				return false;
			}
		}
		// 找到插入的位置，然后创建插入节点
		pCur = new  Node(key,value);
		if (key < pParent->_key)
		{
			pParent->_left = pCur;
		}
		else
		{
			pParent->_right = pCur;
		}
		return true;

		while (pParent)
		{
			if (pParent->_left == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			if (pParent->_bf == 0)
				return true;
			else if (pParent->_bf == 1 || -1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pParent->_parent;
			}
			else
			{
				// 假若这边断键了，保持二叉树的完整性，进行旋转
				if (pParent->_bf == 2)
				{
					if (pCur->_bf == 1)
						_RotateLeft(pParent);
					else
						_RotateRL(pParent);

				}
				else
				{
					if (pCur->_bf == -1)
						_RotateRight(pParent);
					else
						_RotateLR(pParent);
				}
			}

		}	
	}

	// 左旋
	void _RotateLeft(Node* pParent)
	{
		Node *pSubR = pParent->_right;
		Node *pSubRL = pParent->_left;
		pParent->_right = pSubRL;
		if (pSubRL)
		{
			pSubRL->_parent = pParent;
			pSubR->_left = pParent;
			Node *pPParent = pParent->_parent;

			pParent->_parent = pSubR;
			pSubR->_parent = pPParent;
			if (pParent->_parent == nullptr)
				_root = pSubR;
			else
			{
				if (pPParent->_left == pParent)
					pPParent->_left = pSubR;
				else
				{
					pPParent->_right = pSubR;
				}
			}
		}
		// 平衡因子转换为0 ，代表该点平衡
		pParent->_bf = pSubR->_bf = 0;

	}
	// 右旋
	void _RotateRight(Node* pParent)
	{
		Node *pSubL = pParent->_left;
		Node *pSubLR = pParent->_right;
		pParent->_left = pSubLR;
		if (pSubLR)
		{
			pSubLR->_parent = pParent;
			pSubL->_right = pParent;
			Node* pPParent = pParent->_parent;

			pParent->_parent = pSubL;
			pSubL->_parent = pPParent;
			if (pParent->_parent == nullptr)
				_root = pSubL;
			else
			{
				if (pPParent->_left == pParent)
					pPParent->_left = pSubL;
				else
				{
					pPParent->_right = pSubL;
				}
			}
		}
		// 平衡因子转换为0 ，代表该点平衡
		pParent->_bf = pSubL->_bf = 0;
	}

	// 左右旋
	void _RotateLR(Node* pParent) 
	{
		Node* pSubL = pParent->_left;
		Node* pSubLR = pSubL->_right;
		int bf = pSubL->_bf;

		// 递归结算平衡因子
		_RotateLeft(pParent->_left);
		_RotateRight(pParent);
		if (bf == -1)
			pParent->_bf = 1;
		else
			pSubL->_bf = -1;
	}
	// 右左旋
	void _RotateRL(Node* pParent)
	{
		Node* pSubR = pParent->_right;
		Node* pSubRL = pSubR->_left;
		int bf = pSubR->_bf;

		// 递归结算平衡因子
		_RotateRight(pParent->_right);
		_RotateLeft(pParent);
		if (bf == 1)
			pParent->_bf = -1;
		else
			pSubR->_bf = 1;
	}
	// 树的高度
	int Height()
	{
		return _Height(_root);
	}
	// 检测是否平衡，左右子树的高度差绝对值 <=1
	void IsBalanceTree()
	{
		if (_IsBalanceTree(_root))
			cout << "the tree is balanced" << endl;
		else
			cout << "the tree is not balanced" << endl;
	}
	// 前，中，后遍历
	void MidOrder()
	{
		cout << "MidOrder:";
		_MidOrder(_root);
		cout << endl;
	}
	void PreOrder()
	{
		cout << "PreOrder:";
		_PreOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		cout << "PostOrder:";
		_PostOrder(_root);
		cout << endl;
	}
	// 平衡
	bool _IsBalanceTree(Node* root)
	{
		if (root == nullptr)
			return true;
		int LeftHeight = _Height(root->_left);
		int RightHeight = _Height(root->_right);
		if (root->_bf != LeftHeight - RightHeight | abs(root->_bf) > 1)
			return false;
		return true;
	}

private:
	// 函数
	void _MidOrder(Node *root)
	{
		if (root)
		{
			_MidOrder(root->_left);
			cout << root->_key << " ";
			_MidOrder(root->_right);
		}
	}

	void _PreOrder(Node *root)
	{
		if (root)
		{
			cout << root->_key << " ";
			_PreOrder(root->_left);
			_PreOrder(root->_right);
		}
	}

	void _PostOrder(Node *root)
	{
		if (root)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_key << " ";
		}
	}

	// 高度
	int _Height(Node* root)
	{
		if (root == nullptr) return 0;
		if (root->_left == nullptr && root->_right == nullptr) return 1;
		int LeftHeight = _Height(root->_left);
		int RightHeight = _Height(root->_right);
		return LeftHeight > RightHeight ? LeftHeight + 1:RightHeight + 1;
	}

private:
	// 成员
	Node *_root;
};




