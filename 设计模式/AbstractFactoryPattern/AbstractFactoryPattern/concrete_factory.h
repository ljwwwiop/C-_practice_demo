#pragma once
// 工厂模式 

#include "Factory.h"
#include "concrete_product.h"

// 奔驰工厂
class BenzFactory :public Factory 
{
public:
	ICar* CreateCar()
	{
		return new BenzCar();
	}
	IBike* CreateBike()
	{
		return new BenzBike();
	}
};

// 宝马工厂
class BmwFactory :public Factory
{
public:
	ICar* CreateCar()
	{
		return new BmwCar();
	}
	IBike* CreateBike()
	{
		return new BmwBike();
	}
};

// 奥迪工厂
class AudiFactory :public Factory
{
public:
	ICar* CreateCar()
	{
		return new AudiCar();
	}
	IBike* CreateBike()
	{
		return new AudiBike();
	}
};




