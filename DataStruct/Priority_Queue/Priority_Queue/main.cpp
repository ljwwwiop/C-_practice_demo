#include "Heap.h"
#include "Priority_Queue.h"

int main()
{
	Priority_Queue<int, Less<int>> q;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	{
		q.Push(n);
	}
	q.Print_Queue();

	system("pause");
	return 0;
}




