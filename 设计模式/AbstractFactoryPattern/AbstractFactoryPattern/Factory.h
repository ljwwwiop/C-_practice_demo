#pragma once

#include "product.h"

// 抽象工厂模式
class Factory {
public:
	// 枚举
	enum FACTORY_TYPE
	{
		BENZ_FACTORY,
		BMW_FACTORY,
		AUDI_FACTORY
	};

	virtual ICar* CreateCar() = 0; // 创建汽车
	virtual IBike* CreateBike() = 0; //创建自行车
	static Factory*CreateFactory(FACTORY_TYPE factory); // 创建工厂

};
