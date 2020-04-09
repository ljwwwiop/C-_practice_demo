#pragma once

#include "product.h"

// 汽车
// 奔驰
class BenzCar :public ICar {
public:
	string Name() 
	{
		return "Benz Car";
	}
};

// 宝马
class BmwCar :public ICar
{
public:
	string Name()
	{
		return "Bmw Car";
	}
};

 //奥迪
class AudiCar :public ICar
{
public:
	string Name()
	{
		return "Audi Car";
	}
};

// 自行车
class BenzBike :public IBike 
{
public:
	string Name()
	{
		return "Benz Bike";
	}
};

class BmwBike :public IBike
{
public:
	string Name()
	{
		return "Bmw Bike";
	}
};

class AudiBike :public IBike
{
public:
	string Name()
	{
		return "Audi Bike";
	}
};


