//
// @file:           Iterator_traits_template.cpp
// @author:         cuckoo
// @date:           2016/10/21 15:11:30
// @description:    test code for Iterator_traits_template
// @note
//

#include "Iterator_traits_template.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

template <class I>
typename iterator_traits<I>::value_type
func(I iter)
{
	cout << *iter << " ";
}

int main()
{
	vector<int> ivec = { 0, 1, 2, 3, 4, 5 };
	for(auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter)
	{
		func<vector<int>::const_iterator>(iter);
	}

	int num = 6;
	int *ptr = &num;
	func(ptr);

	const char str = 'c';
	func(&str);

	MyIter<const char> myiter(&str);
	func(myiter);

	return 0;
}
