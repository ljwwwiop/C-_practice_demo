/*
	说明：模拟一下真正Lab使用智能指针 PtrDetails的泛型类，存储在垃圾收集信息列表中的元素
	1.  Declare generic class PtrDetails
	2.  Create generics via templates -> 通过模板创建泛型
	3.  All attributes and methods are going to be public, 
		because they are going to be used by other classes
	4.  Create attribute for refcount
	5.  Create attribute memPtr as generic pointer for storage of
		basic info about memory
	6.  Create bool attribute isArray for recognition of memory type allocated
	7.  Create attribute arraySize for working with array allocation
	8.  Declare constructor for PtrDetails which will have two parameters
	9.  First constructor paremeter is going to be pointer and second which is 
		not required, is going to be size of eventual array in memory
	10. We need to construct logic of the constructor which will set 
		isArray attribute if size is larger then 0
	11. Create overload operator == which will be used for comparison 
		between to PtrDetails object in lists. It is mandatory
	unsigned 就是二进制 1000 0001 中间1当作数字，不是正负标识符
*/

template<class T>
class PtrDetails
{
public:
	// holds the reference count
	unsigned refcnt;
	// will point to allocated memory
	T *mptr;
	// true if it is pointing to an array, otherwise, false
	bool isArrall;
	// size of Array
	unsigned arr_size;
	// m_ptr points to the allocated memory
	// size specifies size of the array.
	PtrDetails(T *m_ptr,unsigned size = 0)
	{
		refcnt = 1;
		mptr = m_ptr;
		arr_size = size;
		if (size!= 0)
		{
			isArrall = true;
		}
		else
		{
			isArrall = false;
		}

	}
};

// operator== defines a comparison between two objects
template<class T>
bool operator==(const PtrDetails<T> &obj_1,const PtrDetails<T> &obj_2)
{
	return (obj_1.memPtr == obj_2.memPtr);
}




