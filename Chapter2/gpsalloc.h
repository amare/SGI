//
// @file:           gpsalloc.h
// @author:         cuckoo
// @date:           2016/10/09 11:01:38
// @description:    a simple allocator implementation version
// @note
//

#ifndef _GPSALLOC_H
#define _GPSALLOC_H

#include <new>			// for placement new
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

#include <cstddef>		// for ptrdiff_t, size_t
#include <cstdlib>		// for exit()
#include <climits>		// for UINT_MAX

namespace GPS
{
	template <typename T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		cout << "_allocate" << endl;
		std::set_new_handler(0);	// p240, Effective
		T* temp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if(temp == 0)
		{
			cerr << "out of memory" << endl;
			std::exit(1);
		}

		return temp;
	}

	template <typename T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	template <typename T1, typename T2>
	inline void _construct(T1* p, const T2& arg)
	{
		new(p) T1(arg);		// placement new. p729, Primer
	}

	template <typename T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}

	template <typename T>
	class allocator
	{
	public:
		typedef T         value_type;
		typedef T*        pointer;
		typedef const T*  const_pointer;
		typedef T&        reference;
		typedef const T&  const_reference;
		typedef size_t    size_type;
		typedef ptrdiff_t difference_type;

		// rebind allocator of type U
		template <typename U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		// hint used for locality
		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate(difference_type(n), (pointer)(0));
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T& arg)
		{
			_construct(p, arg);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)(&x);
		}

		const_pointer address(const_reference x) const
		{
			return (const_pointer)(&x);
		}

		size_type max_size() const
		{
			return size_type(UINT_MAX/sizeof(T));
		}

	};	// end of class allocator

}	// end of namespace GPS

#endif // _GPSALLOC_H
