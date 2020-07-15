#include "AdjMatrixDirNetwork.h"

int main()
{
	char vexs[] = "ABCDE";
	AdjMatrixDirNetwork network(vexs,5,5);

	network.InsertArc(0, 1, 10);
	network.InsertArc(0, 4, 70);
	network.InsertArc(0, 3, 30);
	network.InsertArc(1, 2, 50);
	network.InsertArc(2, 4, 10);
	network.InsertArc(3, 2, 20);
	network.InsertArc(3, 4, 60);
	network.Display();

	cout << network.GetWeight(3, 4) << endl;
	cout << network.NextAdjVex(1, 2) << endl;
	cout << network.FirstAdjVex(2) << endl;



	system("pause");
	return 0;
}
