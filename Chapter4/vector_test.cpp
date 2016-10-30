//
// @file:           vector_test.cpp
// @author:         cuckoo
// @date:           2016/10/27 17:50:08
// @description:    a test code for vector 4.2.5
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::find;


int main()
{
	vector<int> iv(2, 9);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(1);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(2);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(3);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(4);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	for(int i = 0; i < iv.size(); ++i)
	{
		cout << iv[i] << ' ';
	}
	cout << endl;

	iv.push_back(5);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for(int i = 0; i < iv.size(); ++i)
	{
		cout << iv[i] << ' ';
	}
	cout << endl;

	iv.pop_back();
	iv.pop_back();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.pop_back();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	vector<int>::iterator iter = find(iv.begin(), iv.end(), 1);
	if(iter != iv.end())
	{
		iv.erase(iter);
	}
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for(int i = 0; i < iv.size(); ++i)
	{
		cout << iv[i] << ' ';
	}
	cout << endl;

	iter = find(iv.begin(), iv.end(), 2);
	if(iter != iv.end())
	{
		iv.insert(iter, 3, 7);
	}
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for(int i = 0; i < iv.size(); ++i)
	{
		cout << iv[i] << ' ';
	}
	cout << endl;

	iv.clear();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	return 0;
}
