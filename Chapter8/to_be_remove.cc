//
// @file:           to_be_remove
// @author:         cuckoo
// @date:           2016/11/23 10:14:43
// @description:    test code for the access of private data in copy constructor
// @note
//

#include <iostream>
using std::cout;
using std::endl;

class ToBeRemove
{
private:
    int to_be_;

public:
    ToBeRemove() { cout << "default constructor" << endl; }
    ToBeRemove(int i) : to_be_(i) { cout << "constructor" << endl; }
    ToBeRemove(const ToBeRemove &rhs) : to_be_(rhs.to_be_) { cout << "copy constructor" << endl; }
    // only constructors take member initializers
    ToBeRemove & operator=(const ToBeRemove &rhs)
    {
        to_be_ = rhs.to_be_;
        cout << "copy assignment operator" << endl;
    }

    void NormalMemberFunction(ToBeRemove &rhs)
    {
        rhs.to_be_ = 5;                             // change the value of rhs's private data
        cout << rhs.to_be_ << endl;
    }

    int to_be() { return to_be_; }
};


int main()
{
    ToBeRemove tobe(4);
    ToBeRemove tobe2 = 3;               // compiler maybe don't use copy constructor(p442, Primer)
    ToBeRemove tobe3 = ToBeRemove(2);
    cout << "========================" << endl;
    ToBeRemove tobe4 = tobe2;
    cout << "========================" << endl;
    ToBeRemove tobe5;
    tobe5 = tobe3;

    cout << tobe2.to_be() << endl;
    tobe5.NormalMemberFunction(tobe2);
    cout << tobe2.to_be() << endl;

    return 0;
}
