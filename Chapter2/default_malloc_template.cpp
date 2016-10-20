//
// @file:           test_default_malloc_template.cpp
// @author:         cuckoo
// @date:           2016/10/20 19:34:40
// @description:    test code for default_malloc_template
// @note
//

#include "default_malloc_template.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

typedef __default_malloc_template<false, 0> default_malloc;

void outOfMem()
{
	cerr << "Unable to satisfy request for memory" << endl;
}

int main()
{
	set_malloc_handler(outOfMem);

	default_malloc allocator;

	int *a16 = (int *)allocator.allocate(sizeof(int)*4);
	if(a16)
	{
		for(int i = 0; i != 4; ++i)
		{
			a16[i] = i;
			cout << "a16[" << i << "] = " << i << endl;
		}
	}
	allocator.deallocate(a16, sizeof(int)*4);

	cout << "sizeof(int): " << sizeof(int) << endl;
	cout << "sizeof(long): " << sizeof(long) << endl;

	std::cout << "==============================================================" << endl;
	int *a64 = (int *)allocator.allocate(sizeof(int)*16);
	allocator.deallocate(a64, sizeof(int)*16);

	std::cout << "==============================================================" << endl;
	int *a129 = (int *)allocator.allocate(sizeof(int)*64);
	allocator.deallocate(a129, sizeof(int)*64);

	return 0;
}
