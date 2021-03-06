//
// @file:           my_iterator_adapter.cc
// @author:         cuckoo
// @date:           2016/11/22 19:13:02
// @description:    test code for iterator adapter
// @note
//

#include <functional>       // for copy
#include <vector>
using std::vector;

#include "Chapter4/my_list.h"

int main()
{
    MyList<int> ilst;
    ilst.push_back(0);
    ilst.push_back(1);
    ilst.push_back(2);
    ilst.push_back(3);

    for(auto iter = ilst.rbegin(); iter != ilst.rend(); ++iter)
        cout << *iter << " ";
    cout << endl;

    cout << "===================" << endl;
    MyList<int>::reverse_iterator iter = ilst.rbegin();
    cout << "===================" << endl;
    cout << *iter << endl;              // 3
    cout << *++++++iter << endl;        // 0
    cout << *--iter << endl;            // 1
    cout << *iter.base() << endl;       // 2

    *iter = 100;
    for(auto iter = ilst.rbegin(); iter != ilst.rend(); ++iter)
        cout << *iter << " ";
    cout << endl;

    auto iter2 = MyList<int>::reverse_iterator();       // don't call copy constructor
                                                        // because rhs is a temporary object??

    int ia[] = { 0, 1, 2, 3, 4, 5 };
    vector<int> iv(ia, ia + 6);
    OstreamIterator<int> out_iterator(cout, " ");
    copy(iv.begin(), iv.end(), out_iterator);

    IstreamIterator<int> in_iterator(cin), eos;
    copy(in_iterator, eos, inserter(iv, iv.begin()));
    copy(iv.begin(), iv.end(), out_iterator);

    return 0;
}
