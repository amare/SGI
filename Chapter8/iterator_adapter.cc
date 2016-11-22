//
// @file:           iterator_adapter.cc
// @author:         cuckoo
// @date:           2016/11/22 09:37:27
// @description:    test program for iterator adapter in Chapter8
// @note
//

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <algorithm>        // for copy

#include <deque>
using std::deque;

#include <iterator>
using std::ostream_iterator;
using std::istream_iterator;

int main()
{
    ostream_iterator<int> out_iterator(cout, " ");

    int ia[] = { 0, 1, 2, 3, 4, 5 };
    deque<int> my_deque(ia, ia + 6);
    copy(my_deque.begin(), my_deque.end(), out_iterator);
    cout << endl;

    copy(ia + 1, ia + 2, front_inserter(my_deque));
    copy(my_deque.begin(), my_deque.end(), out_iterator);
    cout << endl;

    copy(ia + 3, ia + 4, back_inserter(my_deque));
    copy(my_deque.begin(), my_deque.end(), out_iterator);
    cout << endl;

    auto find_result = find(my_deque.begin(), my_deque.end(), 5);
    copy(ia, ia + 3, inserter(my_deque, find_result));
    copy(my_deque.begin(), my_deque.end(), out_iterator);
    cout << endl;

    copy(my_deque.rbegin(), my_deque.rend(), out_iterator);
    cout << endl;

    istream_iterator<int> in_iterator(cin), eos;
    copy(in_iterator, eos, inserter(my_deque, my_deque.begin()));
    copy(my_deque.begin(), my_deque.end(), out_iterator);

    return 0;
}

