//
// @file:           1config5.cpp
// @author:         cuckoo
// @date:           2016/10/05 14:56:41
// @description:    test __STL_CLASS_PARTIAL_SPECIALIZATION
// @note
//

#include <iostream>
using std::cout;
using std::endl;

template <class I, class O>
struct testClass
{
	testClass()
	{
		cout << "I, O" << endl;
	}
};

// partial specialization
template <class T>
struct testClass<T*, T*>
{
	testClass()
	{
		cout << "T*, T*" << endl;
	}
};

// partial specialization
template <class T>
struct testClass<const T*, T*>
{
	testClass()
	{
		cout << "const T*, T*" << endl;
	}
};

int main()
{
	testClass<int, char> obj1;
	testClass<int*, int*> obj2;
	testClass<const int*, int*> obj3;

	return 0;
}
