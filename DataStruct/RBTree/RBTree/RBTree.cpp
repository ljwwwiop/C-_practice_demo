#include "RBTree.h"

// delete node() and find node()
// 这两个函数基本和avl是一样的，可以自己写一下。
int main()
{
	typedef RBTree<int, int> rbt;
	int arr[10] = { 2, 6, 12 ,3, 5, 75 ,45,26,17,22 };
	rbt s;
	for (int i = 0; i < 10; i++)
	{
		s.Insert(arr[i], i);
	}
	
	cout << s.CheckRBTree() << endl;
	s.MidOrder();
	s.Insert(100, 20);
	s.Insert(1, 11);
	s.MidOrder();

	cout << s.CheckRBTree() << endl;
	return 0;
}
