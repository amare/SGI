//
// @file:           tagTest.cpp
// @author:         cuckoo
// @date:           2016/10/21 17:14:17
// @description:    /*info*/
// @note
//

#include <iostream>
using std::cout;
using std::endl;

struct B { };
struct D1 : public B { };
struct D2 : public D1 { };

template <class I>
func(I &p, B)
{
	cout << "B version" << endl;
}

template <class I>
func(I &p, D2)
{
	cout << "D2 version" << endl;
}

int main()
{
	int *p;
	func(p, B());
	func(p, D1());
	func(p, D2());

	return 0;
}
