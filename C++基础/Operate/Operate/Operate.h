#pragma once
// 练习一下重载
#include <iostream>
using namespace std;

class Box {
public:
	Box() {
		hour = 0;
	}

	// 获取 和 设置 get set
	double getVolume(void) 
	{
		return length * height*breadth;
	}
	void setLength(double len) {
		length = len;
	}
	void setBreadth(double bre) {
		breadth = bre;
	}
	void setHeight(double hei) {
		height = hei;
	}
	
	// 描写一个重载方法 + 运算符重载
	Box operator+(const Box& b) 
	{
		Box box;
		box.length = b.length + this->length;
		box.breadth = b.breadth + this->breadth;
		box.height = b.height + this->height;
		return box;
	}

	// 关系符号重载 <>=
	bool operator <(const Box& b) 
	{
		if (length < b.length) {
			return true;
		}
		else {
			return false;
		}
	}

	// 赋值运算符重载
	void operator=(const Box&b) {
		length = b.length;
		height = b.height;
		breadth = b.breadth;
	}

	void print() 
	{
		cout << "length:" << length << endl;
	}

	

private:
	double length;
	double breadth;
	double height;
	int hour;
};

class Time {
private:
	int hours;
	int min;
public:
	Time() 
	{
		hours = 0;
		min = 0;
	}
	Time(int h,int m) 
	{
		hours = h;
		min = m;
	}
	// 显示时间
	void displayTime()
	{
		cout << "H: " << hours << " M:" << min << endl;
	}
	// 重载 前置++
	Time operator++()
	{
		++min;
		if (min >= 60) 
		{
			hours++;
			min -= 60;
		}
		return Time(hours, min);
		// 两种写法
		/*Time t;
		t.hours = ++hours;
		return t;*/
	}
	// 后置++ int 在这表示的是后缀式子的意思
	Time operator++(int)
	{
		Time t(hours, min);
		min++;
		if (min >= 60) {
			++hours;
			min -= 60;
		}
		// 返回原始值，但是下一个值已经改变
		return t;
	}

	
};



