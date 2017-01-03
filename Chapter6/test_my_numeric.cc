//
// @file:           test_numeric.cc
// @author:         cuckoo
// @date:           2016/12/30 16:27:30
// @description:    test code for numeric algorithm
// @note
//

#include "my_numeric.h"
using gps::accumulate;
using gps::InnerProduct;
using gps::PartialSum;
using gps::AdjacentDifference;
using gps::power;
using gps::itoa;

#include <iostream>
using std::cout;
using std::endl;

#include <iterator>
using std::ostream_iterator;

#include <vector>
using std::vector;

#include <functional>
using std::minus;
using std::plus;

#include "Chapter8/my_iterator_adapter.h"

int main()
{
    int ia[] = {1, 2, 3, 4, 5};
    vector<int> iv(ia, ia+5);

    cout << accumulate(iv.begin(), iv.end(), 0) << endl;
    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;

    cout << InnerProduct(iv.begin(), iv.end(), iv.begin(), 10) << endl;
    cout << InnerProduct(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>())
         << endl;

    OstreamIterator<int> oite(cout, " ");
    PartialSum(iv.begin(), iv.end(), oite);
    cout << endl;
    PartialSum(iv.begin(), iv.end(), oite, minus<int>());

    cout << endl;
    AdjacentDifference(iv.begin(), iv.end(), oite);
    cout << endl;
    AdjacentDifference(iv.begin(), iv.end(), oite, plus<int>());

    cout << endl;
    cout << power(10, 3, plus<int>()) << endl;
    cout << power(2, 31) << endl;

    int n = 3;
    itoa(iv.begin(), iv.end(), n);
    for(auto v : iv)
    {
        cout << v << " ";
    }


    return 0;
}
