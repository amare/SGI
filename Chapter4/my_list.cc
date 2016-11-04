//
// @file:           my_list.cc
// @author:         cuckoo
// @date:           2016/10/30 20:34:02
// @description:    /*info*/
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include "my_list.h"

#include <algorithm>
using std::find;

int main()
{
	MyList<int> ilst;
	cout << "size = " << ilst.size() << endl;

	ilst.push_back(0);
	ilst.push_back(1);
	ilst.push_back(2);
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	ilst.push_front(3);
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
	ilst.pop_back();
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
	ilst.pop_front();
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	ilst.push_back(1);
	ilst.push_back(2);
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
	ilst.remove(1);
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	ilst.clear();
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;


	ilst.push_back(0);
	ilst.push_back(1);
	ilst.push_back(9);

	MyList<int> ilst2;
	ilst2.push_back(2);
	ilst2.push_back(3);
	ilst2.push_back(4);
	ilst2.push_back(5);
	ilst2.push_back(6);
	ilst2.push_back(7);
	ilst2.push_back(8);

	MyList<int>::iterator iter = find(ilst.begin(), ilst.end(), 9);
	ilst.splice(iter, ilst2);
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	ilst.reverse();
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	ilst.sort();
	for(auto iter = ilst.begin(); iter != ilst.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}
