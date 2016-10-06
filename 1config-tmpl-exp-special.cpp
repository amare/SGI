//
// @file:           1config-tmpl-exp-special
// @author:         cuckoo
// @date:           2016/10/06 10:06:38
// @description:    test template explicit specialization
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#define __STL_TEMPLATE_NULL template<>		// there must be template<> before explicit specialization

template <class Key>
struct hash
{
	void operator() ()
	{
		cout << "hash<Key>" << endl;
	}
};

// explicit specialization
__STL_TEMPLATE_NULL
struct hash<char>
{
	void operator() ()
	{
		cout << "hash<char>" << endl;
	}
};

__STL_TEMPLATE_NULL
struct hash<unsigned char>
{
	void operator() ()
	{
		cout << "hash<unsigned char>" << endl;
	}
};

int main()
{
	hash<long> t1;
	hash<char> t2;
	hash<unsigned char> t3;

	t1();
	t2();
	t3();

	return 0;
}
