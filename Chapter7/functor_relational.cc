//
// @file:           functor_relational.cc
// @author:         cuckoo
// @date:           2016/11/21 23:12:11
// @description:    /*info*/
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
using std::equal_to;
using std::not_equal_to;
using std::greater;
using std::greater_equal;
using std::less;
using std::less_equal;

int main()
{
    equal_to<int> equal_to_obj;
    not_equal_to<int> not_equal_to_obj;
    greater<int> greater_obj;
    greater_equal<int> greater_equal_obj;
    less<int> less_obj;
    less_equal<int> less_equal_obj;

    cout << equal_to_obj(5, 3) << endl;
    cout << not_equal_to_obj(5, 3) << endl;
    cout << greater_obj(5, 3) << endl;
    cout << greater_equal_obj(5, 3) << endl;
    cout << less_obj(5, 3) << endl;
    cout << less_equal_obj(5, 3) << endl;


    cout << equal_to<int>()(5, 3) << endl;
    cout << not_equal_to<int>()(5, 3) << endl;
    cout << greater<int>()(5, 3) << endl;
    cout << greater_equal<int>()(5, 3) << endl;
    cout << less<int>()(5, 3) << endl;
    cout << less_equal<int>()(5, 3) << endl;

    return 0;
}

