#include <iostream>
#include <stdio.h>
/*
	用来记录测试 指针/引用之类的
	引用只是别名
	函数参数 int &x 可以直接实参和形参被使用
	const int &x 时可以赋值 给函数内部变量，但自不能被修改 这个做参数比上面好  接受左值/和不匹配类型的参数
	比如long long
	
*/
using namespace std;

void f( const int &x)
{
	int p = x;
	cout<< p<<endl;

}


int main()
{
	int p = 5;
	int q = 7;
	int *const x = &p;
	long l = 100001;
	int &y = q;
	//q = 10;
	y = 99;
	
	cout<<  *x <<endl;
	cout << y << endl;
	cout << "q:" << &q << endl;
	f(l);
	cout << "f:"<< q << endl;

	system("pause");
	return 0;
}


