//
// @file:           1config.cpp
// @author:         cuckoo
// @date:           2016/09/29 22:07:01
// @description:    test configurations defined in <c++config.h>
// @note
//

//#include <vector>
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

	// case 6
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
	cout << "__STL_FUNCTION_TMPL_PARTIAL_ORDER defined" << endl;
#else
	cout << "__STL_FUNCTION_TMPL_PARTIAL_ORDER defined" << endl;
#endif

	// case 7
#ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
	cout << "__STL_EXPLICIT_FUNCTION_TMPL_ARGS defined" << endl;
#else
	cout << "__STL_EXPLICIT_FUNCTION_TMPL_ARGS defined" << endl;
#endif

	// case 8
#ifdef __STL_MEMBER_TEMPLATES
	cout << "__STL_MEMBER_TEMPLATES defined" << endl;
#else
	cout << "__STL_MEMBER_TEMPLATES defined" << endl;
#endif

	// case 10
#ifdef __STL_LIMITED_DEFAULT_TEMPLATES
	cout << "__STL_LIMITED_DEFAULT_TEMPLATES defined" << endl;
#else
	cout << "__STL_LIMITED_DEFAULT_TEMPLATES defined" << endl;
#endif

	// case 11
#ifdef __STL_NON_TYPE_TMPL_PARAM_BUG
	cout << "__STL_NON_TYPE_TMPL_PARAM_BUG defined" << endl;
#else
	cout << "__STL_NON_TYPE_TMPL_PARAM_BUG defined" << endl;
#endif

	// case 12
#ifdef __SGI_STL_NO_ARROW_OPERATOR
	cout << "__SGI_STL_NO_ARROW_OPERATOR defined" << endl;
#else
	cout << "__SGI_STL_NO_ARROW_OPERATOR defined" << endl;
#endif

	// case 13
#ifdef __STL_USE_EXCEPTIONS
	cout << "__STL_USE_EXCEPTIONS defined" << endl;
#else
	cout << "__STL_USE_EXCEPTIONS defined" << endl;
#endif

	// case 14
#ifdef __STL_USE_NAMESPACES
	cout << "__STL_USE_NAMESPACES defined" << endl;
#else
	cout << "__STL_USE_NAMESPACES defined" << endl;
#endif

	// case 15
#ifdef __STL_SGI_THREADS
	cout << "__STL_SGI_THREADS defined" << endl;
#else
	cout << "__STL_SGI_THREADS defined" << endl;
#endif

	// case 16
#ifdef __STL_WIN32THREADS
	cout << "__STL_WIN32THREADS defined" << endl;
#else
	cout << "__STL_WIN32THREADS defined" << endl;
#endif

	// case 19
#ifdef __STL_ASSERTIONS
	cout << "__STL_ASSERTIONS defined" << endl;
#else
	cout << "__STL_ASSERTIONS defined" << endl;
#endif

	cout << "============================" << std::endl;

#ifdef __STL_NEED_BOOL
	cout << "__STL_NEED_BOOL defined" << endl;
#else
	cout << "__STL_NEED_BOOL defined" << endl;
#endif


#ifdef __STL_NEED_TYPENAME
	cout << "__STL_NEED_TYPENAME defined" << endl;
#else
	cout << "__STL_NEED_TYPENAME defined" << endl;
#endif


#ifdef __STL_NEED_EXPLICIT
	cout << "__STL_NEED_EXPLICIT defined" << endl;
#else
	cout << "__STL_NEED_EXPLICIT defined" << endl;
#endif


#ifdef __STL_NO_NAMESPACES
	cout << "__STL_NO_NAMESPACES defined" << endl;
#else
	cout << "__STL_NO_NAMESPACES defined" << endl;
#endif

	return 0;
}
