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

#include <cstddef>		// for ptrdiff_t

// #define DEBUG

struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };


template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type         value_type;
	typedef typename Iterator::difference_type    difference_type;
	typedef typename Iterator::pointer            pointer;
	typedef typename Iterator::reference          reference;
	typedef typename Iterator::iterator_category  iterator_category;
};

template <class T>
struct iterator_traits<T *>
{
	typedef T                           value_type;
	typedef ptrdiff_t                   difference_type;
	typedef T*                          pointer;
	typedef T&                          reference;
	typedef random_access_iterator_tag  iterator_category;
};

template <class T>
struct iterator_traits<const T *>
{
	typedef T                           value_type;
	typedef ptrdiff_t                   difference_type;
	typedef const T*                    pointer;
	typedef const T&                    reference;
	typedef random_access_iterator_tag  iterator_category;
};

template <class T>
struct MyIter
{
	typedef T                           value_type;
	typedef ptrdiff_t                   difference_type;
	typedef T*                          pointer;
	typedef T&                          reference;
	typedef random_access_iterator_tag  iterator_category;

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


template <class InputIterator, class Distance>
inline void _advance(InputIterator &i, Distance n, input_iterator_tag)
{
	while(n--) ++i;
}

template <class InputIterator, class Distance>
inline void _advance(InputIterator &i, Distance n, bidirectional_iterator_tag)
{
	if(n >= 0)
		while(n--) ++i;
	else
		while(n++) --i;
}

template <class InputIterator, class Distance>
inline void _advance(InputIterator &i, Distance n, random_access_iterator_tag)
{
	i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator &i, Distance n)
{
	_advance(i, n, iterator_traits<InputIterator>::iterator_category());
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}
