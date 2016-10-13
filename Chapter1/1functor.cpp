//
// @file:           1functor.cpp
// @author:         cuckoo
// @date:           2016/10/06 13:34:23
// @description:    operator() overloading
// @note
//

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
struct plus
{
	T operator()(const T &x, const T &y) const
	{
		return x + y;
	}
};

template <typename T>
struct minus
{
	T operator()(const T &x, const T &y) const
	{
		return x - y;
	}
};

int main()
{
	plus<int> plusobj;
	minus<int> minusobj;

	cout << plusobj(3, 5) << endl;
	cout << minusobj(3, 5) << endl;

	// create a temporary function object(using the first couple parentheses)
	// and then call operator()(using the second couple parentheses)
	cout << plus<int>()(43, 50) << endl;
	cout << minus<int>()(43, 50) << endl;

	return 0;
}
