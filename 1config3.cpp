//
// @file:           1config3.cpp
// @author:         cuckoo
// @date:           2016/09/30 21:56:57
// @description:    test __STL__STATIC_TEMPLATE_MEMBER_BUG
// @note
//

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class testClass
{
	public:
		static string _data;
};

// initialization of static data member in a template class
// need total template specialization
template<>
string testClass<int>::_data = "int";

template<>
string testClass<char>::_data = "char";

int main()
{
	std::cout << "testClass<int>::_data\t" << testClass<int>::_data << std::endl;
	std::cout << "testClass<char>::_data\t" << testClass<char>::_data << std::endl;

	std::cout << "==========================" << std::endl;
	testClass<int> obji1, obji2;
	testClass<char> objc1, objc2;

	std::cout << "obji1._data\t" << obji1._data << std::endl;
	std::cout << "obji2._data\t" << obji2._data << std::endl;
	std::cout << "objc1._data\t" << objc1._data << std::endl;
	std::cout << "objc2._data\t" << objc2._data << std::endl;

	std::cout << "====== re-assignment =====" << std::endl;
	obji1._data = "newint";
	objc2._data = "newchar";

	std::cout << "obji1._data\t" << obji1._data << std::endl;
	std::cout << "obji2._data\t" << obji2._data << std::endl;
	std::cout << "objc1._data\t" << objc1._data << std::endl;
	std::cout << "objc2._data\t" << objc2._data << std::endl;

	return 0;
}

