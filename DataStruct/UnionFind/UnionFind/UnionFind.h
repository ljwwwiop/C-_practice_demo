#pragma once
// 并查集 UnionFind,主要用来查看图中是否存在环

#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
public:
	UnionFind(int x) 
	{
		_setbit.resize(x + 1,- 1);
	}

	int FindRoot(int x)
	{
		while (_setbit[x] >= 0)
		{
			x = _setbit[x];
		}
		return x;
	}

	void Union(int x, int y)
	{
		int Root1 = FindRoot(x);
		int Root2 = FindRoot(y);

		if (Root1 != Root2)
		{
			_setbit[Root1] += _setbit[Root2];
			_setbit[Root2] = Root1;
		}
	}

	int Size()
	{
		int count = 0;
		for (int i = 0; i < _setbit.size(); i++)
		{
			if (_setbit[i] < 0)
				++count;
		}
		return count - 1;
	}

private:
	vector<int> _setbit;
};

int Friend(const int n,const int m ,int r[][4])
{
	UnionFind un(n);
	for (int i = 0; i < m; ++i)
	{
		un.Union(r[i][0], r[i][1]);
	}

	return un.Size();
}

void TestUnionFind()
{
	const int n = 5;
	const int m = 4;
	int r[n][4] = { {1,2},{2,3},{4,5},{3,4} };
	int num = Friend(n, m, r);
	cout << num << endl;
}


