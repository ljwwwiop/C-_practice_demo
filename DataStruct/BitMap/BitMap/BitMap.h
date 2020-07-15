#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 位图只能处理整数
// 不能提供模板类型

class BitMap
{
public:
	BitMap(size_t range) 
	{
		// 一共多少个字节，余数，所以+1
		_bits.resize(range>>3 +1,0);
	}
	void Set(size_t value)
	{
		// 计算出那个字节
		size_t index = (value >> 3);
		// 计算出具体哪个位
		size_t num = value % 8;
		// 将该位置为1
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



