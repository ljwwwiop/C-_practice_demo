#include "gc_pointer.h"
#include "LeakTester.h"

int main()
{
	Pointer<int> p = new int(19);
	p = new int(20);
	p = new int(21);

	Pointer<int, 3> ptr = new int[3]{ 1,2,3 };
	ptr = new int[3]{ 4,5,6 };

	return 0;

}

