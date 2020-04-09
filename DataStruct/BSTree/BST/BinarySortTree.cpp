#include "BinarySortTree.h"

int main()
{
	typedef BSTree<int, int> BST;
	int a[10] = { 5, 3, 1, 4, 0, 2, 7, 6, 8, 9 };
	BST s;
	for (int i = 0; i < 10; i++)
	{
		s.Insert_R(a[i], i);
	}
	s.MidOrder();
	s.Remove(5);
	s.MidOrder();
	s.Remove_R(2);
	s.PreOrder();
	s.Insert(100, 20);
	s.MidOrder();
	s.Height();

	return 0;
}


