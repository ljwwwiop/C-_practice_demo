#pragma once
#include<iostream>

/*
	��д����һ�Ŷ�����
*/

struct BinaryTreeNode
{
	BinaryTreeNode *_Left;
	BinaryTreeNode *_Right;
	int _value;
};

BinaryTreeNode* ConstructCore(int *StartPreorder, int *EndPreorder, int *StartInorder, int *EndInorder);

BinaryTreeNode* Construct(int *PreOrder,int *InOrder,size_t length)
{
	if (PreOrder == NULL || InOrder == NULL || length <= 0)
	{
		return NULL;
	}
	return ConstructCore(PreOrder, PreOrder + length - 1, InOrder, InOrder + length - 1);
}

BinaryTreeNode* ConstructCore(int *StartPreorder, int *EndPreorder, int *StartInorder, int *EndInorder)
{
	// ǰ���һ���ڵ����root
	int RootValue = StartPreorder[0];
	BinaryTreeNode* Root = new BinaryTreeNode();
	Root->_value = RootValue;
	Root->_Left = Root->_Right = NULL;

	if (StartPreorder == EndPreorder)
	{
		
		if (StartInorder == EndInorder && *StartPreorder == *StartInorder) // ֻ��һ���ڵ�ʱ��
			return Root;
		else
			throw std::exception("error Invalid Input");
	
	}

	int *RootInOrder = StartInorder;
	while (RootInOrder <= EndInorder && *RootInOrder != RootValue)//����������Ľ�����Ҹ����
		++RootInOrder;

	if (RootInOrder == EndInorder && *RootInOrder != RootValue) // ����������û���ҵ����
		throw std::exception("Invalid Input");

	// �ߵ�����˵���������ҵ���ROOT�ڵ�
	int LeftLenght = RootInOrder - StartInorder;
	int *LeftPreOrderEnd = StartInorder + LeftLenght; //����������leftlength��Ϊ������

	if (LeftLenght > 0)
	{
		// ����������
		Root->_Left = ConstructCore(StartPreorder +1,LeftPreOrderEnd,StartInorder,RootInOrder - 1);
	}
	if (LeftLenght < EndPreorder - StartPreorder)
	{
		// ����������
		Root->_Right = ConstructCore(LeftPreOrderEnd + 1, EndPreorder, RootInOrder + 1, EndInorder);
	}

	return Root;
}

void PrintBinaryTree(BinaryTreeNode *Root)
{
	// �����ӡ
	if (Root == NULL)
		return;
	PrintBinaryTree(Root->_Left);
	PrintBinaryTree(Root->_Right);
	std::cout << Root->_value << " ";
}

void Test(const char* testName,int* preorder,int* inorder,int length)
{
	if (testName != NULL) printf("%s begins:\n",testName);

	printf("The preorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", preorder[i]);
	printf("\n");

	printf("The inorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", inorder[i]);
	printf("\n");

	try
	{
		BinaryTreeNode* root = Construct(preorder, inorder, length);
		PrintBinaryTree(root);
		std::cout << std::endl;
	}
	catch (const std::exception& )
	{
		printf("Invalid Input.\n");
	}



}
//***************************************************
//����������
//***************************************************

// ��ͨ������
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
	const int length = 8;
	int preorder[length] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inorder[length] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	Test("Test1", preorder, inorder, length);
}

// ���н�㶼û�����ӽ��
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 5, 4, 3, 2, 1 };

	Test("Test2", preorder, inorder, length);
}

// ���н�㶼û�����ӽ��
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 1, 2, 3, 4, 5 };

	Test("Test3", preorder, inorder, length);
}

// ����ֻ��һ�����
void Test4()
{
	const int length = 1;
	int preorder[length] = { 1 };
	int inorder[length] = { 1 };

	Test("Test4", preorder, inorder, length);
}


// ��ȫ������
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 5, 1, 6, 3, 7 };

	Test("Test5", preorder, inorder, length);
}

// �����ָ��
void Test6()
{
	Test("Test6", NULL, NULL, 0);
}

// ������������в�ƥ��
void Test7()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 8, 1, 6, 3, 7 };

	Test("Test7: for unmatched input", preorder, inorder, length);
}

