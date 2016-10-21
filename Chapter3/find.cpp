//
// @file:           find.cpp
// @author:         cuckoo
// @date:           2016/10/21 10:30:54
// @description:    containers, algorithms, and iterator
// @note
//

#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
#include <algorithm>
using std::find;
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	const int arraySize = 7;
	int ia[arraySize] = { 0, 1, 2, 3, 4, 5, 6 };

	vector<int> ivec(ia, ia+arraySize);
	list<int> ilist(ia, ia+arraySize);
	deque<int> ideq(ia, ia+arraySize);

	vector<int>::const_iterator it1 = find(ivec.cbegin(), ivec.cend(), 0);
	if(ivec.cend() == it1)
		cout << "0 not found." << endl;
	else
		cout << "0 found: " << *it1 << endl;

	list<int>::const_iterator it2 = find(ilist.cbegin(), ilist.cend(), 3);
	if(ilist.cend() == it2)
		cout << "3 not found." << endl;
	else
		cout << "3 found: " << *it2 << endl;

	deque<int>::const_iterator it3 = find(ideq.cbegin(), ideq.cend(), 7);
	if(ideq.cend() == it3)
		cout << "7 not found." << endl;
	else
		cout << "7 found: " << *it3 << endl;

	return 0;
}
