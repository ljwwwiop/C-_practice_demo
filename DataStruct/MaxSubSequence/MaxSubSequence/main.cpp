#include "MaxSubSeq.h"

int main()
{
	int n, *a, i;
	cout << "���������ĸ���n:";
	cin >> n;
	a = new int[n];
	cout << "����������:";
	for (i = 0; i < n; i++)
		cin >> a[i];
	MaxSubSeq_1(n, a);
	MaxSubSeq_2(n, a);
	delete[] a;
	return 0;
}


