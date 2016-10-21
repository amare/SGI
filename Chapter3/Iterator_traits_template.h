//
// @file:           Iterator_traits_template.h
// @author:         cuckoo
// @date:           2016/10/21 15:06:50
// @description:    get associated types of Iterator
// @note
//

#include <iostream>
using std::cout;
using std::endl;

// #define DEBUG

template <class I>
struct iterator_traits
{
	typedef typename I::value_type value_type;
};

template <class T>
struct iterator_traits<T *>
{
	typedef T value_type;
};

template <class T>
struct iterator_traits<const T *>
{
	typedef T value_type;
};

template <class T>
struct MyIter
{
	typedef T value_type;
	T *ptr;

	MyIter(T *p = 0): ptr(p) {}
	T & operator*() const
	{
		#ifdef DEBUG
			cout << "MyIter" ;
		#endif
		return *ptr;
	}
};
