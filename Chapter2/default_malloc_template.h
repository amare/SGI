//
// @file:           default_malloc_template.h
// @author:         cuckoo
// @date:           2016/10/20 16:17:17
// @description:    sub-allocation
// @note
//

#ifndef DEFAULT_MALLOC_TEMPLATE_H
#define DEFAULT_MALLOC_TEMPLATE_H

// #define DEBUG

#include "malloc_alloc_template.h"
#include <iostream>
using std::cout;
using std::endl;

#include <cstddef>		// for size_t
#include <iostream>
using std::cout;
using std::endl;
using std::hex;
using std::dec;

enum { __ALIGN = 8 };
enum { __MAX_BYTES = 128 };
enum { __NFREELISTS = __MAX_BYTES/__ALIGN };

template <bool threads, int inst>
class __default_malloc_template
{
private:
	static size_t ROUND_UP(size_t bytes)
	{
		return ((bytes + __ALIGN-1) & ~(__ALIGN - 1));
	}

	union obj
	{
		union obj * free_list_link;
		char client_data[1];
	};

	static obj * volatile free_list[__NFREELISTS];
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN-1)/__ALIGN - 1);
	}

	static void * refill(size_t n);
	static char * chunk_alloc(size_t size, int &nobjs);

	static char * start_free;
	static char * end_free;
	static size_t heap_size;

public:
	static void * allocate(size_t n);		// n must be > 0
	static void deallocate(void *p, size_t n);
	static void outputFreeList();
};

template <bool threads, int inst>
char * __default_malloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char * __default_malloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_malloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
typename __default_malloc_template<threads, inst>::obj * volatile
__default_malloc_template<threads, inst>::free_list[__NFREELISTS] =
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


template <bool threads, int inst>
void * __default_malloc_template<threads, inst>::allocate(size_t n)
{
	#ifdef DEBUG
	cout << "====== default_malloc::allocate(" << n << ") MB ======" << endl;
	#endif
	obj * volatile * my_free_list;
	obj * result;

	if(n > (size_t)__MAX_BYTES)
	{
		return __malloc_alloc_template<inst>::allocate(n);
	}

	my_free_list = free_list + FREELIST_INDEX(n);
	result = *my_free_list;
	if(0 == result)
	{
		void *ret = refill(ROUND_UP(n));
		#ifdef DEBUG
		outputFreeList();
		#endif
		return ret;
	}

	*my_free_list = result->free_list_link;
	#ifdef DEBUG
	outputFreeList();
	#endif
	return result;
}

template <bool threads, int inst>
void __default_malloc_template<threads, inst>::deallocate(void *p, size_t n)
{
	#ifdef DEBUG
	cout << "====== default_malloc::deallocate() ======" << endl;
	#endif
	if(n > (size_t)__MAX_BYTES)
	{
		__malloc_alloc_template<inst>::deallocate(p, n);
		return ;
	}

	obj *q = (obj *)p;
	obj * volatile *my_free_list = free_list + FREELIST_INDEX(n);
	q->free_list_link = *my_free_list;
	*my_free_list = q;

	#ifdef DEBUG
	outputFreeList();
	#endif
}

template <bool threads, int inst>
void * __default_malloc_template<threads, inst>::refill(size_t n)
{
	#ifdef DEBUG
	cout << "====== refill(" << n << ") ======" << endl;
	#endif
	int nobjs = 20;
	char *chunk = chunk_alloc(n, nobjs);

	if(1 == nobjs)
	{
		return chunk;
	}

	obj * result;
	obj * current_obj, * next_obj;
	obj * volatile * my_free_list;
	my_free_list = free_list + FREELIST_INDEX(n);

	result = (obj *)chunk;
	*my_free_list = next_obj = (obj *)(chunk + n);

	for(int i = 1; ; ++i)
	{
		current_obj = next_obj;
		next_obj = (obj *)((char *)next_obj + n);

		if(nobjs-1 == i)
		{
			current_obj->free_list_link = 0;
			break;
		}
		else
		{
			current_obj->free_list_link = next_obj;
		}
	}

	return result;
}

template <bool threads, int inst>
char * __default_malloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs)
{
	#ifdef DEBUG
	cout << "====== chunk_alloc(" << size << ", " << nobjs << ") ======" << endl;
	#endif
	char * result;
	size_t bytes_left = end_free - start_free;
	size_t total_bytes = size * nobjs;

	if(bytes_left >= total_bytes)
	{
		result = start_free;
		start_free += bytes_left;
		return result;
	}
	else if(bytes_left >= size)
	{
		nobjs = bytes_left / size;
		result = start_free;
		total_bytes = size * nobjs;
		start_free += total_bytes;
		return result;
	}
	else
	{
		size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);

		if(bytes_left > 0)
		{
			obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
			((obj *)start_free)->free_list_link = *my_free_list;
			*my_free_list = (obj *)start_free;
		}

		start_free = (char *)malloc(bytes_to_get);
		if(0 == start_free)
		{
			obj * volatile *my_free_list, *p;
			for(int i = size; i <= __MAX_BYTES; i += __ALIGN)
			{
				my_free_list = free_list + FREELIST_INDEX(i);
				p = *my_free_list;
				if(0 != p)
				{
					*my_free_list = p->free_list_link;
					start_free = (char *)p;
					end_free = start_free + i;
					return chunk_alloc(size, nobjs);
				}
			}
			end_free = 0;
			start_free = (char *)__malloc_alloc_template<inst>::allocate(bytes_left);
		}

		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;

		return chunk_alloc(size, nobjs);
	}
}

template <bool threads, int inst>
void __default_malloc_template<threads, inst>::outputFreeList()
{
	cout << "====== outputFreeList() ======" << endl;
	for(int i = 0; i < __NFREELISTS; ++i)
	{
		cout << "#" << i << ":" << endl;
		obj *p = free_list[i];
		int count = 0;
		while(p)
		{
			cout << hex << p << " ";
			p = p->free_list_link;
			if(0 == ++count % 4)
			{
				cout << endl;
			}
		}
		cout << dec << endl;
	}
}

#endif
