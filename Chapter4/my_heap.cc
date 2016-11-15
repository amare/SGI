//
// @file:           my_heap.cc
// @author:         cuckoo
// @date:           2016/11/12 16:05:53
// @description:    a test code for my_heap
// @note
//

#include "my_heap.h"


#include "stl_heap.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main()
{
	{
		int ia[10] = { 68, 31, 65, 21, 24, 32, 26, 19, 16, 13 };
		vector<int> my_heap(ia, ia+10);

		my_heap.push_back(50);
		PushHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;

		cout << "===============================" << endl;
		PopHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;
		my_heap.pop_back();
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;

		cout << "===============================" << endl;
		SortHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;


		cout << "================================================" << endl;
		int ia2[10] = { 68, 31, 65, 21, 24, 32, 26, 19, 16, 13 };
		vector<int> my_heap2(ia2, ia2+10);

		my_heap2.push_back(50);
		PushHeap(my_heap2.begin(), my_heap2.end());
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;

		cout << "===============================" << endl;
		pop_heap(my_heap2.begin(), my_heap2.end());
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;
		my_heap2.pop_back();
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;

		cout << "===============================" << endl;
		sort_heap(my_heap2.begin(), my_heap2.end());
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;
	}

/*	{
		int ia[8] = { 60, 58, 20, 44, 42, 16, 18, 30};
		vector<int> iv(ia, ia+8);

		PopHeap(iv.begin(), iv.end());
		iv.pop_back();
		for(auto item : iv)
			cout << item << " ";
		cout << endl;
	}
*/
/*
	{
		int ia[10] = { 68, 31, 65, 21, 24, 32, 26, 19, 16, 13 };
		vector<int> my_heap(ia, ia+10);

		SortHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;
	}
*/
/*
	{
		cout << "==================================" << endl;
		// int ia[4] = { 1, 4, 3, 2 };
		// int ia[11] = { 68, 50, 65, 21, 31, 32, 26, 19, 16, 13, 24 };
		int ia[12] = { 89, 23, 43, 100, 127, 82, 25, 45, 105, 18, 8, 94 };
		vector<int> my_heap(ia, ia+12);

		MakeHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;
		cout << "----------------------------------" << endl;

		SortHeap(my_heap.begin(), my_heap.end());
		for(auto elem : my_heap)
			cout << elem << " ";
		cout << endl;


		cout << "==================================" << endl;
		// int ia2[4] = { 1, 4, 3, 2 };
		// int ia2[11] = { 68, 50, 65, 21, 31, 32, 26, 19, 16, 13, 24 };
		int ia2[12] = { 89, 23, 43, 100, 127, 82, 25, 45, 105, 18, 8, 94 };
		vector<int> my_heap2(ia2, ia2+12);

		make_heap(my_heap2.begin(), my_heap2.end());
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;

		sort_heap(my_heap2.begin(), my_heap2.end());
		for(auto elem : my_heap2)
			cout << elem << " ";
		cout << endl;
	}
*/
	return 0;
}
