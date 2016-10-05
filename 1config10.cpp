//
// @file:           1config10.cpp
// @author:         cuckoo
// @date:           2016/10/05 18:14:31
// @description:    test __STL_LIMITED_DEFAULT_TEMPLATES
// @note
//

#include <iostream>
using std::cout;
using std::endl;

class alloc
{

};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{
	public:
		deque()
		{
			cout << "deque()" << endl;
		}
};

// set Sequence to a default template argument value(deque<T>)
// which is based on the front argument T
template <class T, class Sequence = deque<T>>
class stack
{
	public:
		stack()
		{
			cout << "stack()" << endl;
		}

	private:
		Sequence c;
};

int main()
{
	stack<int> x;

	return 0;
}
