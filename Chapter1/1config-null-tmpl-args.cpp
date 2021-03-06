//
// @file:           1config-null-tmpl-args
// @author:         cuckoo
// @date:           2016/10/05 20:54:59
// @description:    test null template arguments
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

// forward declaration, needed by friend function declaration in class stack
template <class T, class Sequence> class stack;		// needed by parameter in operator==

template <class T, class Sequence>
bool operator==(const stack<T, Sequence> &, const stack<T, Sequence> &);

template <class T, class Sequence>
bool operator<(const stack<T, Sequence> &, const stack<T, Sequence> &);
// ====== END forward declaration

template <class T, class Sequence = deque<T>>
class stack
{
	// This is right
	friend bool operator==<T> (const stack<T> &, const stack<T> &);		//(1)
	friend bool operator< <T> (const stack<T> &, const stack<T> &);

	// This is also right
	//friend bool operator==<T> (const stack &, const stack &);
	//friend bool operator< <T> (const stack &, const stack &);
	// also right
	//friend bool operator==<> (const stack &, const stack &);	// null template arguments
	//friend bool operator< <> (const stack &, const stack &);
	// wrong
	//friend bool operator==(const stack &, const stack &);	// non-template-friend

	// friend bool operator==<T, Sequence> (const stack<T, Sequence> &,
	// 	const stack<T, Sequence> &);		// same to above (1)

	public:
		stack()
		{
			cout << "stack()" << endl;
		}

	private:
		Sequence c;
};

template <class T, class Sequence>
bool operator==(const stack<T, Sequence> &lhs, const stack<T, Sequence> &rhs)
{
	return cout << "operator==" << '\t';
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence> &lhs, const stack<T, Sequence> &rhs)
{
	return cout << "operator<" << '\t';
}

int main()
{
	stack<int> stk1, stk2;
	cout << (stk1 == stk2) << endl;
	cout << (stk1 < stk2) << endl;

	stack<int, char> stk3;
	// cout << (stk1 == stk3) << endl;		// no match for operator==
	// cout << (stk2 < stk3) << endl;		// no match for operator<

	// added to test git status flag(AM)
	return 0;
}
