#include <iostream>

using namespace std;

class Shape {
public:
	Shape();
	void calcArea(); // 虚函数
	~Shape();  // 虚析构函数
};

Shape::Shape() 
{
	cout << "这是构造函数！" << endl;
}
Shape::~Shape() 
{
	cout << "析构函数" << endl;
}
void Shape::calcArea() 
{
	cout << "计算方法" << endl;
}

int main()
{
	Shape *a = new Shape();
	a->calcArea();
	delete a;
	a = NULL;
	return 0;
}


