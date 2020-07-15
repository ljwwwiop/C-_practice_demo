#pragma once
/*
	经典算法题目 -> 最大子序列和问题
*/

#include <iostream>
#include <algorithm>

using namespace std;

// 两种解题思路
// 算法一，暴力算出每个子序列得和，直接找出最大得，时间复杂度0(n^2)
void MaxSubSeq_1(int n, int *Seq)
{
	int i, j, MaxSum = 0, sum = 0;
	for ( i = 0; i < n; i++)
	{
		// 判断是否全都小于0
		if (Seq[i] >= 0)
			break;
	}
	if (i == n)
	{
		MaxSum = Seq[0];
		for ( i = 1; i < n; i++)
			if (Seq[i] > MaxSum)
				MaxSum = Seq[i];
		cout << "最大子序列和为" << MaxSum << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			// 从第0位到第n-1位
			for (int j = i; j < n; j++)
			{
				sum = sum + Seq[j];
				MaxSum = max(MaxSum, sum);
			}
			sum = 0;
		}
		cout << "最大子序列和为" << MaxSum << endl;
	}

}

// 解法二
// 联机算法，在线处理，时间复杂度o(n)
void MaxSubSeq_2(int n, int *Seq)
{
	int i, j, MaxSum = 0, sum = 0;
	for (i = 0; i < n; i++)
	{
		if (Seq[i] >= 0)
			break;
	}

	if (i == n)
	{
		MaxSum = Seq[0];
		for ( i = 1; i < n; i++)
			if (Seq[i] > MaxSum)
				MaxSum = Seq[i];
		cout << "最大子序列和为" << MaxSum << endl;
	}
	else
	{
		// 不全为负情况
		for (int i = 0; i < n; i++)
		{
			sum = sum + Seq[i];
			if (sum <= 0) // 假如出现负数，不可能使后面的部分和更大，所以没意义
				sum = 0; // 直接清零，下一项开始
			else
			{
				MaxSum = max(sum, MaxSum);
			}
		}
		cout << "最大子序列和为" << MaxSum << endl;
	}
	

}


