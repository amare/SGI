//
// @file:           1config-inclass-init.cpp
// @author:         cuckoo
// @date:           2016/10/06 12:01:56
// @description:    const static integral data member initialization
// @note
//

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class staticClass
{
	public:
		static constexpr int _datai = 5;
		static constexpr long _datal = 3L;
		static constexpr char _datac = 'c';
};

int main()
{
	cout << staticClass<int>::_datai << endl;
	cout << staticClass<int>::_datal << endl;
	cout << staticClass<int>::_datac << endl;

	return 0;
}
