#include "GenList.h"

int main()
{
	char str[] = "((a,b),c,d,(e,()))", str2[] = "(a,(b,(c,d,())),c)";
	GenList glist(str), copylist(glist), glist2(str2);
	
	cout << glist << endl;
	cout << copylist << endl;
	cout << "�˱�����Ϊ:" << glist.GetDepth() << endl;

	copylist = glist2;
	cout << copylist << endl;
	cout << "�˱�����Ϊ:" << copylist.GetDepth() << endl;
	return 0;
}

