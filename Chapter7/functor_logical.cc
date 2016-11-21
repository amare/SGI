//
// @file:           functor_logical.cc
// @author:         cuckoo
// @date:           2016/11/21 23:19:08
// @description:    /*info*/
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
using std::logical_and;
using std::logical_or;
using std::logical_not;

int main()
{
    logical_and<int> and_obj;
    logical_or<int> or_obj;
    logical_not<int> not_obj;

    cout << and_obj(true, true) << endl;
    cout << or_obj(true, false) << endl;
    cout << not_obj(true) << endl;


    cout << logical_and<int>()(true, true) << endl;
    cout << logical_or<int>()(true, false) << endl;
    cout << logical_not<int>()(true) << endl;

    return 0;
}
