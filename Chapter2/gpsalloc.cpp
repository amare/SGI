//
// @file:           gpsalloc.cpp
// @author:         cuckoo
// @date:           2016/10/09 16:22:45
// @description:    test code for simple allocator implement version in gpsalloc.h
// @note
//

#include "gpsalloc.h"
#include <vector>
#include <iostream>
using std::cout;

template <typename T>
void foo(int a, T)		// T is only for the template argument deduction
{
	cout << a << endl;
}

int main()
{
	foo(6, 7);		// 7 -> T(int)

	int ia[5] = {0, 1, 2, 3, 4};

	std::vector<int, GPS::allocator<int>> iv(ia, ia+5);
	for(auto i : iv)
		cout << i << " ";
	cout << endl;

	return 0;
}
