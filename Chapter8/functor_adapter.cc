//
// @file:           fuctor_adapter.cc
// @author:         cuckoo
// @date:           2016/11/22 15:15:44
// @description:    test program for functor adapter in Chapter8
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <iterator>
using std::ostream_iterator;

#include <algorithm>        // for copy, count_if, transform

#include <vector>
using std::vector;

#include <functional>
using std::multiplies;
using std::plus;
using std::less;
using std::greater_equal;
using std::ptr_fun;
using std::mem_fun_ref;

#include <ext/functional>   // for compose1

void NormalFunctionPrint(int i)
{
    cout << i << " ";
}

class MemberPrint
{
public:
    explicit MemberPrint(int i ) : i_(i) { }

    void printf1() const { cout << '[' << i_ << ']'; }

private:
    int i_;
};

int main()
{
    ostream_iterator<int> out_iterator(cout, " ");
    int ia[] = { 2, 21, 12, 7, 19, 23 };
    vector<int> iv(ia, ia + 6);

    cout << count_if(iv.begin(), iv.end(), not1(bind2nd(less<int>(), 12))) << endl;
    cout << count_if(iv.begin(), iv.end(), bind2nd(greater_equal<int>(), 12)) << endl;

    transform(iv.begin(), iv.end(), out_iterator, __gnu_cxx::compose1(
                                                    bind2nd(multiplies<int>(), 3),
                                                    bind2nd(plus<int>(), 2)));
    cout << endl;


    copy(iv.begin(), iv.end(), out_iterator);
    cout << endl;

    // (1) pointer to function
    for_each(iv.begin(), iv.end(), NormalFunctionPrint);
    cout << endl;
    // (2) normal function processed by ptr_fun
    for_each(iv.begin(), iv.end(), ptr_fun(NormalFunctionPrint));
    cout << endl;


    // (3) member function processed by mem_fun_ref
    MemberPrint p1(3), p2(7), p3(20), p4(14), p5(68);
    vector<MemberPrint> member_vector;
    member_vector.push_back(p1);
    member_vector.push_back(p2);
    member_vector.push_back(p3);
    member_vector.push_back(p4);
    member_vector.push_back(p5);
    for_each(member_vector.begin(), member_vector.end(), mem_fun_ref(&MemberPrint::printf1));


    return 0;
}
