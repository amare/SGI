//
// @file:           functor_arthmetic.cc
// @author:         cuckoo
// @date:           2016/11/21 23:02:46
// @description:    /*info*/
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::modulus;
using std::negate;

int main()
{
    plus<int> plus_obj;
    minus<int> minus_obj;
    multiplies<int> multiplies_obj;
    divides<int> divides_obj;
    modulus<int> modulus_obj;
    negate<int> negate_obj;

    cout << plus_obj(3, 5) << endl;
    cout << minus_obj(3, 5) << endl;
    cout << multiplies_obj(3, 5) << endl;
    cout << divides_obj(3, 5) << endl;
    cout << modulus_obj(3, 5) << endl;
    cout << negate_obj(3) << endl;


    cout << plus<int>()(3, 5) << endl;
    cout << minus<int>()(3, 5) << endl;
    cout << multiplies<int>()(3, 5) << endl;
    cout << divides<int>()(3, 5) << endl;
    cout << modulus<int>()(3, 5) << endl;
    cout << negate<int>()(3) << endl;

    return 0;
}
