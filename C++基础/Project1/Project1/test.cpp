// 主要用来写算法和C++小测试的项目
// 2020/2/16  - > 堆排序  ->  桶排序  -> 归并排序 -> 计数排序
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

// 堆排序 1 建立（大/小）顶堆 2 堆排序
void max_heapify(int arr[], int start, int end) {
	//建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son] < arr[son + 1]) //先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { //否則交換父子內容再繼續子節點和孫節點比較
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	//初始化，i從最後一個父節點開始調整
	for (int i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	//先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}


}

// 桶排序

// 计数排序
void CountSort(vector<int>& vecRaw, vector<int>& vecObj)
{
	// 确保待排序容器非空
	if (vecRaw.size() == 0)
		return;

	// 使用 vecRaw 的最大值 + 1 作为计数容器 countVec 的大小
	int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
	vector<int> vecCount(vecCountLength, 0);

	// 统计每个键值出现的次数
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;

	// 后面的键值出现的位置为前面所有键值出现的次数之和
	for (int i = 1; i < vecCountLength; i++)
		vecCount[i] += vecCount[i - 1];

	// 将键值放到目标位置
	for (int i = vecRaw.size(); i > 0; i--)	// 此处逆序是为了保持相同键值的稳定性
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
}

// 插入查找 类似二分查找
/*int InsertSearch(int* a,int value,int low,int high) 
{
	int mid =low+(value - a[low])/(a[high] - a[low])*(high - low) ;
	if (a[mid] == value)
		return mid;
	if (a[mid] > value)
		return InsertSearch(a,value,low,mid-1);
	if(a[mid] < value)
		return InsertSearch(a, value, mid + 1, high);
}*/

// 快排序
int Propotion(int *A,int low,int high) 
{
	int p = A[low];
	while (low < high) 
	{
		while (low < high && A[high] >= p)
			high--;
		A[low] = A[high];
		while (low < high && A[low] <= p)
			low++;
		A[high] = A[low];
	}
	A[low] = p;
	return low;
}

void QuickSort(int *A,int low,int high)
{
	if (low < high)
	{
		int p = Propotion(A, low, high);
		QuickSort(A, low, p - 1);
		QuickSort(A, p + 1, high);
	}

}


int main()
{
	// 堆排序
	int arr[] = { 3, 5, 3, 0, 8, 5, 9, 7, 4, 0, 2, 6 };
	int len = (int)sizeof(arr) / sizeof(*arr);
	/*for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
	heap_sort(arr, len);
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
	heap_sort(arr,len);*/
	
	// 计数排序
	/*vector<int> vecRaw = { 0,5,7,9,6,3,4,5,2,8,6,9,2,1 };
	vector<int> vecObj(vecRaw.size(), 0);
	for (int i = 0; i < vecObj.size(); ++i)
		cout << vecRaw[i] << "  ";
	cout << endl;
	CountSort(vecRaw, vecObj);
	for (int i = 0; i < vecObj.size(); ++i)
		cout << vecObj[i] << "  ";
	cout << endl;*/

	// 快排序
	QuickSort(arr, 0, len - 1);
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}


