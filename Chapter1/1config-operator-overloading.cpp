//
// @file:           1config-operator-overloading.cpp
// @author:         cuckoo
// @date:           2016/10/06 12:57:30
// @description:    increment/decrement/dereference operator
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <ostream>
using std::ostream;

class INT
{
	friend ostream & operator<<(ostream &, const INT &);
	public:
		INT(int i): m_i(i) {}

		// prefix: increment and fetch
		INT & operator++()
		{
			++(this->m_i);
			return *this;
		}

		// postfix: fetch and increment
		INT operator++(int)
		{
			INT temp = *this;
			++(*this);
			return temp;
		}

		// prefix: decrement and fetch
		INT & operator--()
		{
			--(this->m_i);
			return *this;
		}

		// postfix: fetch and decrement
		INT operator--(int)
		{
			INT temp = *this;
			--(*this);
			return temp;
		}

		// dereference
		int & operator*() const
		{
			return (int&)m_i;		// tell compiler to convert const int converts to non-const lvalue
		}

	private:
		int m_i;
};

ostream & operator<<(ostream &os, const INT &i)
{
	os << '[' << i.m_i << ']';
	return os;
}

int main()
{
	INT I(5);
	cout << I++ << endl;
	cout << ++I << endl;
	cout << I-- << endl;
	cout << --I << endl;
	cout << *I << endl;

	return 0;
}
