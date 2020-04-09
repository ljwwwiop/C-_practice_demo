#include "FactoryMain.h"
#include "product.h"
#include "Factory.h"
#include <iostream>

using namespace std;

void FactoryMain() 
{
	// สตภýปฏ
	Factory *pFactory = Factory::CreateFactory(Factory::FACTORY_TYPE::BENZ_FACTORY);
	ICar *car = pFactory->CreateCar();
	IBike *bike = pFactory->CreateBike();

	cout << "Benz factory - car" << car->Name() << endl;
	cout << "Benz factory - bike" << bike->Name() << endl;

	SAFE_DELETE(car);
	SAFE_DELETE(bike);
	SAFE_DELETE(pFactory);
}

