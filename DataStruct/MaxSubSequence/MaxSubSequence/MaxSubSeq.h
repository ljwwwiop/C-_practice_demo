#pragma once
/*
	�����㷨��Ŀ -> ��������к�����
*/

#include <iostream>
#include <algorithm>

using namespace std;

// ���ֽ���˼·
// �㷨һ���������ÿ�������еúͣ�ֱ���ҳ����ã�ʱ�临�Ӷ�0(n^2)
void MaxSubSeq_1(int n, int *Seq)
{
	int i, j, MaxSum = 0, sum = 0;
	for ( i = 0; i < n; i++)
	{
		// �ж��Ƿ�ȫ��С��0
		if (Seq[i] >= 0)
			break;
	}
	if (i == n)
	{
		MaxSum = Seq[0];
		for ( i = 1; i < n; i++)
			if (Seq[i] > MaxSum)
				MaxSum = Seq[i];
		cout << "��������к�Ϊ" << MaxSum << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			// �ӵ�0λ����n-1λ
			for (int j = i; j < n; j++)
			{
				sum = sum + Seq[j];
				MaxSum = max(MaxSum, sum);
			}
			sum = 0;
		}
		cout << "��������к�Ϊ" << MaxSum << endl;
	}

}

// �ⷨ��
// �����㷨�����ߴ���ʱ�临�Ӷ�o(n)
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
		cout << "��������к�Ϊ" << MaxSum << endl;
	}
	else
	{
		// ��ȫΪ�����
		for (int i = 0; i < n; i++)
		{
			sum = sum + Seq[i];
			if (sum <= 0) // ������ָ�����������ʹ����Ĳ��ֺ͸�������û����
				sum = 0; // ֱ�����㣬��һ�ʼ
			else
			{
				MaxSum = max(sum, MaxSum);
			}
		}
		cout << "��������к�Ϊ" << MaxSum << endl;
	}
	

}


