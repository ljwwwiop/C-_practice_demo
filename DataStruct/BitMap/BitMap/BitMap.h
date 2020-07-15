#pragma once
#include <iostream>
#include <vector>
using namespace std;

// λͼֻ�ܴ�������
// �����ṩģ������

class BitMap
{
public:
	BitMap(size_t range) 
	{
		// һ�����ٸ��ֽڣ�����������+1
		_bits.resize(range>>3 +1,0);
	}
	void Set(size_t value)
	{
		// ������Ǹ��ֽ�
		size_t index = (value >> 3);
		// ����������ĸ�λ
		size_t num = value % 8;
		// ����λ��Ϊ1
		_bits[index] |= (1 << num);
	}

	void ReSet(size_t value)
	{
		size_t index = (value >> 3);
		size_t num = value % 8;

		_bits[index] &= (~(1 << num));

	}

	bool Test(size_t value)
	{
		size_t index = (value >> 3);
		size_t num = value % 8;
		return _bits[index] & (1 << num);
	}

private:
	vector<char> _bits;

};

void TestBitMap()
{
	BitMap bt(100);

	bt.Set(2);
	bt.Set(16);
	bt.Set(24);

	cout << bt.Test(2) << " ";
	cout << bt.Test(16) << " ";
	cout << bt.Test(24) << " ";
	cout << endl;

	bt.ReSet(2);
	bt.ReSet(24);

	cout << bt.Test(2) << " ";
	cout << bt.Test(16) << " ";
	cout << bt.Test(24) << " ";
}



