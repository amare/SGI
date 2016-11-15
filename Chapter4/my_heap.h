//
// @file:           my_heap.h
// @author:         cuckoo
// @date:           2016/11/12 15:27:04
// @description:    heap algorithm implementation in SGI STL
// @note
//

#ifndef SGI_CHAPTER4_MY_HEAP_H_
#define SGI_CHAPTER4_MY_HEAP_H_

#include <iostream>
using std::cout;
using std::endl;

#include "Chapter3/iterator_traits_template.h"

#define GPS_DEBUG_

// push_heap algorithm
template <typename RandomAccessIterator, typename Distance, typename T>
void _PushHeapAux(RandomAccessIterator first, Distance hole_index, Distance top_index, T value)
{
	Distance parent = (hole_index - 1) / 2;
	while(hole_index > top_index && *(first + parent) < value)
	{
		// percolate up
		*(first + hole_index) = *(first + parent);
		hole_index = parent;
		parent = (hole_index - 1) / 2;
	}
	*(first + hole_index) = value;
}

template <typename RandomAccessIterator, typename Distance, typename T>
inline void PushHeapAux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
{
	_PushHeapAux(first, Distance((last - 1) - first), Distance(0), T(*(last - 1)));
}

// attention: before call, new element must have been at the end of the container
template <typename RandomAccessIterator>
inline void PushHeap(RandomAccessIterator first, RandomAccessIterator last)
{
	PushHeapAux(first, last, distance_type(first), value_type(first));
}

// pop_heap algorithm
template <typename RandomAccessIterator, typename Distance, typename T>
void AdjustHeap(RandomAccessIterator first, Distance hole_index, Distance len, T value)
{
#if !defined(GPS_DEBUG_)
	cout << "len: " << len << "\tvalue: " << value << endl;
#endif
	Distance top_index = hole_index;
	Distance bigger_child = hole_index * 2 + 2;		// default to the right child
	while(bigger_child < len)		// has right child
	{
		if(*(first + bigger_child) < *(first + (bigger_child - 1)))
			--bigger_child;			// the left child is bigger
		// percolate down
	#if !defined(GPS_DEBUG_)
		cout << "---------------------------" << endl;
		cout << "hole_index: " << hole_index << " bigger_child: " << bigger_child << endl;
	#endif
		*(first + hole_index) = *(first + bigger_child);
		hole_index = bigger_child;
		// *(first + hole_index) = value;		//@gps
		bigger_child = hole_index * 2 + 2;
	}
	#if !defined(GPS_DEBUG_)
		cout << "---------- final ----------" << endl;
		cout << "hole_index: " << hole_index << " bigger_child: " << bigger_child << endl;
	#endif
	if(bigger_child == len)		// only has left child
	{
	#if !defined(GPS_DEBUG_)
		cout << *(first + hole_index) << endl;
	#endif
		*(first + hole_index) = *(first + (len - 1));
		// hole_index = bigger_child - 1;
		*(first + (len - 1)) = value;
		return;
	}
#if !defined(GPS_DEBUG_)
	cout << "==============================" << endl;
	for(int i = 0; i < len; ++i)
		cout << *(first + i) << " ";
	cout << endl;
	cout << "hole_index: " << hole_index << endl;
	cout << "top_index: " << top_index << endl;
	cout << "value: " << value << endl;
#endif
	// the original last element of the container must be re-insert to container becasue
	// it has been replaced by the max element(located at top_index before pop), at the
	// same time, hole-index must be filled. So insert the last element(value) into the
	// hold_index, and excute percolate up process.
	_PushHeapAux(first, hole_index, top_index, *(first + (len - 1)));		//@gps correct
	*(first + (len - 1)) = value;		//@gps add
}

template <typename RandomAccessIterator, typename T, typename Distance>
inline void _PopHeapAux(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator result, T value, Distance*)
{
	// *result = *first;		//@gps delete
#if !defined(GPS_DEBUG_)
	cout << "result: " << *result << endl;
	cout << "first: " << *first << " last: " << *last << Distance(last - first) << endl;
#endif
	AdjustHeap(first, Distance(0), Distance(last - first), value);
}

template <typename RandomAccessIterator, typename T>
inline void PopHeapAux(RandomAccessIterator first, RandomAccessIterator last, T*)
{
	_PopHeapAux(first, last, last - 1, T(*first), distance_type(first));
}

template <typename RandomAccessIterator>
inline void PopHeap(RandomAccessIterator first, RandomAccessIterator last)
{
	PopHeapAux(first, last, value_type(first));
}

// sort_heap algorithm
template <typename RandomAccessIterator>
void SortHeap(RandomAccessIterator first, RandomAccessIterator last)
{
	while(last - first > 1)
	{
		PopHeap(first, last--);
	#if !defined(GPS_DEBUG_)
		for(auto iter = first; iter != last; ++iter)
			cout << *iter << " ";
		cout << endl;
	#endif
	}
}

// make_heap algorithm
template <typename RandomAccessIterator, typename Distance, typename T>
void AdjustHeap2(RandomAccessIterator first, Distance hole_index, Distance len, T value)
{
	Distance top_index = hole_index;

	Distance bigger_child = hole_index * 2 + 2;
	while(bigger_child < len)
	{
		if(*(first + bigger_child) < *(first + (bigger_child - 1)))
			--bigger_child;
		*(first + hole_index) = *(first + bigger_child);
		hole_index = bigger_child;
		bigger_child = hole_index * 2 + 2;
	}
	if(bigger_child == len)
	{
		*(first + hole_index) = *(first + (bigger_child - 1));
		hole_index = bigger_child - 1;
	}
	_PushHeapAux(first, hole_index, top_index, value);
}

template <typename RandomAccessIterator, typename T, typename Distance>
void MakeHeapAux(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
{
	if(last - first < 2) return;
	Distance len = last - first;

	Distance hole_index = (len - 2) / 2;
	while(true)
	{
		AdjustHeap2(first, hole_index, len, *(first + hole_index));
	#if defined(GPS_DEBUG_)
		for(auto iter = first; iter != first + len; ++iter)
			cout << *iter << " ";
		cout << endl;
	#endif
		if(hole_index == 0) return;
		--hole_index;
	}
}

template <typename RandomAccessIterator>
inline void MakeHeap(RandomAccessIterator first, RandomAccessIterator last)
{
	MakeHeapAux(first, last, value_type(first), distance_type(first));
}

#endif
