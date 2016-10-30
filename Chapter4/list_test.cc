//
// @file:           list_test.cc
// @author:         cuckoo
// @date:           2016/10/30 17:12:08
// @description:    a test code for list
// @note
//

#include <iostream>
using std::cout;
using std::endl;
#include <list>
using std::list;
#include <algorithm>
using std::find;

int main()
{
	list<int> ilist;
	cout << "size = " << ilist.size() << endl;

	ilist.push_back(0);
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);
	ilist.push_back(4);
	cout << "size = " << ilist.size() << endl;

	list<int>::iterator iter;
	for(iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	iter = find(ilist.begin(), ilist.end(), 3);
	if(iter != ilist.end())
	{
		ilist.insert(iter, 99);
		cout << *iter << endl;
		cout << "size = " << ilist.size() << endl;
	}

	for(iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	iter = find(ilist.begin(), ilist.end(), 1);
	if(iter != ilist.end())
	{
		cout << *(ilist.erase(iter)) << endl;
		cout << "size = " << ilist.size() << endl;
	}

	for(iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << " ";
	cout << endl;

	return 0;
}
