//
// @file:           malloc_alloc_template
// @author:         cuckoo
// @date:           2016/10/13 09:52:35
// @description:    2.2.5, p56
// @note
//

#if 0
#	include<new>
#	define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#	include<iostream>
#	define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1)
#endif

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::hex;
using std::dec;

template <int inst>
class __malloc_alloc_template
{
public:
	static void * allocate(size_t n)
	{
		cout << "====== malloc_alloc::allocate(" << n << ") MB ======" << endl;
		void *result = malloc(n);
		// result = 0;		/* test code */
		// malloc failed, call oom_malloc()
		if(0 == result)
			result = oom_malloc(n);

		return result;
	}

	static void deallocate(void *p, size_t n = 0/* n */)
	{
		cout << "====== malloc_alloc::deallocate(" << hex << p << dec << ", " << n << ") ======" << endl;
		free(p);
	}

	static void * reallocate(void *p, size_t/* old_sz */, size_t new_sz)
	{
		void * result = realloc(p, new_sz);
		// reallocate failed, call oom_realloc()
		// result = 0;		/* test code */
		if(0 == result)
			result = oom_realloc(p, new_sz);

		return result;
	}

	static void (* __malloc_alloc_oom_handler)();

private:
	// fucntions which handle out of memory
	static void *oom_malloc(size_t);
	static void *oom_realloc(void *, size_t);
};

// malloc_alloc out-of-memory handling
// initialized to 0, and waited to be specified using set_malloc_handler() by user
template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
	void (* my_malloc_handler)();
	void *result;
	while(true)		// ask for memory until malloc successes
	{
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler)
		{
			__THROW_BAD_ALLOC;		//@gps: __THROW_BAD_ALLOC are two statements, must be
									// included in Braces
		}
		(*my_malloc_handler)();		// call handler processing, trying to release memory

		result = malloc(n);		// try to malloc again
		if(result)
		{
			return result;
		}
	}
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
	void (* my_malloc_handler)();
	void *result;

	while(true)
	{
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler)
		{
			__THROW_BAD_ALLOC;		//@gps: __THROW_BAD_ALLOC are two statements, must be
									// included in Braces
		}
		(*my_malloc_handler)();

		result = realloc(p, n);
		if(result)
			return result;
	}
}

// same functor to set_new_handler in C++
// see p223, Primer & p240, Effective
static void (* set_malloc_handler(void (*f)()))()
{
	void (* old)() = __malloc_alloc_template<0>::__malloc_alloc_oom_handler;
	__malloc_alloc_template<0>::__malloc_alloc_oom_handler = f;

	return old;
}
