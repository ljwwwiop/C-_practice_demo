/*
	auther: @ByLian
	time: 2020/4/6
*/
#include "AVLTree.h"
#define N 10

int main()
{
	int a[N] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };
	AVLTree<int, int> t;
	for (int i = 0; i < N; i++)
	{
		t.Insert(a[i],i);
	}

	t.IsBalanceTree();
	t.MidOrder();
	t.PostOrder();
	t.PreOrder();
	cout << "Height:" << t.Height() << endl;

	return 0;
}

