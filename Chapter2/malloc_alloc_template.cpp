//
// @file:           malloc_alloc_template.cpp
// @author:         cuckoo
// @date:           2016/10/13 10:58:53
// @description:    test code for malloc_alloc_template
// @note
//


#include "malloc_alloc_template.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

typedef __malloc_alloc_template<0> malloc_alloc;

void outOfMem()
{
	cerr << "Unable to satisfy request for memory" << endl;
}

int main()
{
	malloc_alloc allocator;

	set_malloc_handler(outOfMem);

	int *a = (int *)allocator.allocate(4*sizeof(int));

	if(a)
	{
		for(int i = 0; i != 4; ++i)
		{
			a[i] = i;
			cout << "a[" << i << "] = " << i << endl;
		}
	}

	cout << "===============================" << endl;
	int *b = (int *)allocator.reallocate((void *)a, 4*sizeof(int), 5*sizeof(int));
	if(b)
	{
		for(int i = 0; i != 5; ++i)
		{
			b[i] = i;
			cout << "b[" << i << "] = " << i << endl;
		}
	}

	// allocator.deallocate(a);		//@gps: Once call of realloc() successes, the original
									// pointer ptr is invalidated and any access to it is undefined behavior
	allocator.deallocate(b);

	return 0;
}
