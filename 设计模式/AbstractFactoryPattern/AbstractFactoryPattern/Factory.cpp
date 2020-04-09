#include "Factory.h"
#include "concrete_factory.h"

Factory* Factory::CreateFactory(FACTORY_TYPE factory)
{
	Factory *pFactory = nullptr;
	switch (factory)
	{
	case FACTORY_TYPE::BENZ_FACTORY:
		pFactory = new BenzFactory();
		break;
	case FACTORY_TYPE::BMW_FACTORY:
		pFactory = new BmwFactory();
		break;
	case FACTORY_TYPE::AUDI_FACTORY:
		pFactory = new AudiFactory();
		break;
	default:
		break;
	}
	return pFactory;
};

