//
// @file:           my_construct.h
// @author:         cuckoo
// @date:           2016/10/31 19:47:34
// @description:    for ctor and dtor
// @note
//

#ifndef SGI_CHAPTER4_MY_CONSTRUCT_H_
#define SGI_CHAPTER4_MY_CONSTRUCT_H_

#include "Chapter3/iterator_traits_template.h"
#include "my_type_traits.h"

#include <new>

template <typename T1, typename T2>
inline void construct(T1 *p, const T2& value)
{
	new (p) T1(value);
}

template <typename T>
inline void destroy(T* pointer)
{
	pointer->~T();
}

template <typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, value_type(first));
}

template <typename ForwardIterator, typename T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*)
{
	typedef typename TypeTraits<T>::has_trivial_destructor trivial_destructor;
	__destroy_aux(first, last, trivial_destructor());
}

template <typename ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, FalseType)
{
	for(; first < last;  ++first)
	{
		destroy(&*first);
	}
}

template <typename ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, TrueType) { }

inline void destroy(char*, char*) { }
inline void destroy(wchar_t*, wchar_t*) { }

#endif
