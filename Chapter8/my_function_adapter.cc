//
// @file:           my_function_adapter.cc
// @author:         cuckoo
// @date:           2016/11/28 15:35:18
// @description:    test code for my_function adapter
// @note
//

#include "my_function_adapter.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>        // for count_if

#include <functional>
using std::less;
using std::multiplies;
using std::plus;

#include "my_iterator_adapter.h"

int main()
{
    OstreamIterator<int> out_iterator(cout, " ");

    int ia[] = { 1, 2, 3, 4, 5, 6 };
    vector<int> iv(ia, ia + 6);

    cout << count_if(iv.begin(), iv.end(), gps::not1(gps::bind2nd(less<int>(), 3))) << endl;

    transform(iv.begin(), iv.end(), out_iterator, gps::compose1(
                                                    gps::bind2nd(multiplies<int>() , 3),
                                                    gps::bind2nd(plus<int>(), 2) ));
    cout << endl;

    transform(iv.begin(), iv.end(), out_iterator, gps::compose2(
                                                    multiplies<int>(),
                                                    gps::bind2nd(multiplies<int>(), 1),
                                                    gps::bind2nd(multiplies<int>(), 1) ));

    return 0;
}
