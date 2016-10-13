//
// @file:           1config8.cpp
// @author:         cuckoo
// @date:           2016/10/05 17:36:27
// @description:    test __STL_MEMBER_TEMPLATES
// @note
//

#include <iostream>
using std::cout;
using std::endl;

class alloc
{

};

template <class T, class Alloc = alloc>
class vector
{
	public:
		typedef T valuetype;
		typedef valuetype *iterator;

	// member function is also a template
	template <class I>
	void insert(iterator position, I first, I last)
	{
		cout << "insert()" << endl;
	}
};

int main()
{
	int ia[5] = {0, 1, 2, 3, 4};

	vector<int> ivec;
	vector<int>::iterator iter;
	ivec.insert(iter, ia, ia+5);

	return 0;
}

