//
// @file:           1config.cpp
// @author:         cuckoo
// @date:           2016/09/29 22:07:01
// @description:    test configurations defined in <c++config.h>
// @note
//

#include <vector>
#include <iostream>

using namespace std;

int main()
{
#	if defined(__sgi)
	cout << "__sgi" << endl;
#	endif

#	if defined(__GNUC__)
	cout << "__GNUC__" << endl;
	cout << __GNUC__ << " " << __GNUC_MINOR__ << endl;
#	endif

	// case 2
#ifdef __STL_NO_DRAND48
	cout << "__STL_NO_DRAND48 defined" << endl;
#else
	cout << "__STL_NO_DRAND48 undefined" << endl;
#endif

	// case 3
#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
	cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG defined" << endl;
#else
	cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG undefined" << endl;
#endif

	// case 5
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
	cout << "__STL_CLASS_PARTIAL_SPECIALIZATION defined" << endl;
#else
	cout << "__STL_CLASS_PARTIAL_SPECIALIZATION defined" << endl;
#endif

	return 0;
}
