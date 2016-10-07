//
// @file:           1config-tempObj.cpp
// @author:         cuckoo
// @date:           2016/10/06 11:00:24
// @description:    create a temporary function object for generic algorithms
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <ostream>
using std::ostream;

#include <vector>
#include <algorithm>

template <typename ElemType>
class PrintElem
{
	public:
		PrintElem(ostream &o = cout, char c = ' '): os(o), sep(c){}

		void operator()(const ElemType &elem) const
		{
			os << elem << sep;
		}

	private:
		ostream &os;
		char sep;
};

int main()
{
	int ia[6] = {0, 1, 2, 3, 4, 5};
	std::vector<int> iv(ia, ia+6);

	// PrintElem<int>(cout, '_') is a temporary funciton object, not a function call
	for_each(iv.cbegin(), iv.cend(), PrintElem<int>(cout, '_'));

	return 0;
}
