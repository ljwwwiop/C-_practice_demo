#include "KMP.h"
#include <iostream>
using namespace std;

int main()
{
	string ob = "abcaacabb", pat = "caa";
	cout << KMP_Find(ob, pat);

	system("pause");
	return 0;
}
