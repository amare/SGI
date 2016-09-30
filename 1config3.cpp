//
// @file:           1config3.cpp
// @author:         cuckoo
// @date:           2016/09/30 21:56:57
// @description:    test __STL__STATIC_TEMPLATE_MEMBER_BUG
// @note
//

#include <iostream>
using namespace std;

template<typename T>
class testClass
{
	public:
		static char _data;
};

// initialization of static data member in a template class
// need total template specialization
template<>
char testClass<int>::_data = 'i';

template<>
char testClass<char>::_data = 'c';

int main()
{
	std::cout << testClass<int>::_data << std::endl;
	std::cout << testClass<char>::_data << std::endl;

	testClass<int> obji1, obji2;
	testClass<char> objc1, objc2;

	std::cout << obji1._data << std::endl;
	std::cout << obji2._data << std::endl;
	std::cout << objc1._data << std::endl;
	std::cout << objc2._data << std::endl;

	obji1._data = 'j';
	objc2._data = 'h';

	std::cout << obji1._data << std::endl;
	std::cout << obji2._data << std::endl;
	std::cout << objc1._data << std::endl;
	std::cout << objc2._data << std::endl;

	return 0;
}

