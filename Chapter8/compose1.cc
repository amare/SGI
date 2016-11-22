//
// @file:           compose1.cc
// @author:         cuckoo
// @date:           2016/11/22 10:49:46
// @description:    test program for functor adapter compose1 in Chapter8
// @note
//

#include <iterator>
using std::ostream_iterator;

#include <vector>
using std::vector;

#include <algorithm>        // for copy, for_each, transform

#include <functional>
using std::multiplies;
using std::plus;

#include <iostream>
using std::cout;
using std::endl;

#include <ext/functional>

int main()
{
    ostream_iterator<int> out_iterator(cout, " ");

    int ia[] = { 2, 21, 12, 7, 19, 23 };
    vector<int> iv(ia, ia + 6);

    for_each(iv.begin(), iv.end(), __gnu_cxx:: compose1(
                                    bind2nd(multiplies<int>(), 3),
                                    bind2nd(plus<int>(), 2)));
    copy(iv.begin(), iv.end(), out_iterator);
    cout << endl;

    transform(iv.begin(), iv.end(), out_iterator, __gnu_cxx::compose1(
                                    bind2nd(multiplies<int>(), 3),
                                    bind2nd(plus<int>(), 2)));
    cout << endl;

    return 0;
}
