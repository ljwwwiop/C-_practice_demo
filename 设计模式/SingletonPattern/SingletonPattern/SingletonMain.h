#pragma once
// 单例模式 ，懒汉单例，线程安全的单例

#include "Singleton.h"

void SingletonMain()
{
	Singleton::GetInstance().DoSomething();
}

