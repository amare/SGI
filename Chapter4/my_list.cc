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

	return 0;
}
