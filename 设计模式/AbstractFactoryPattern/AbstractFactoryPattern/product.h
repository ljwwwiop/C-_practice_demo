#pragma once

// 定义接口
#include <string>
using std::string;

// 汽车接口
class ICar {
public:
	virtual string Name() = 0;

};

// 自行车接口
class IBike {
public:
	virtual string Name() = 0;
};

