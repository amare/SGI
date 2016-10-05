//
// @file:           1config6.cpp
// @author:         cuckoo
// @date:           2016/10/05 16:31:39
// @description:    test __STL_FUNCTION_TMPL_PARTIAL_ORDER
// @note
//

#include <iostream>
using std::cout;
using std::endl;

class alloc
{

};

template <class T, class Alloc = alloc>
class vector
{
	public:
		void swap(vector<T, Alloc> &)
		{
			cout << "swap()" << endl;
		}
};

int main()
{
	vector<int> x,y;
	//swap(x, y);		//not define __STL_FUNCTION_TMPL_PARTIAL_ORDER

	return 0;
}

