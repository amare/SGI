//
// @file:           test_using.cpp
// @author:         cuckoo
// @date:           2016/10/10 11:14:34
// @description:    a test code for alias template and macros with parameters
// @note
//

#include <iostream>
using std::cout;
using std::endl;

// macros with parameters, see http://en.cppreference.com/w/cpp/preprocessor/replace
#define _self_GLIBCXX_PSEUDO_VISIBILITY(V) cout << #V << endl;
#define _self_GLIBCXX_VISIBILITY(V) _self_GLIBCXX_PSEUDO_VISIBILITY(V)

namespace __self_gnu_cxx
{
	template <typename _Tp>
	class new_allocator
	{
	public:
		new_allocator()
		{
			cout << "new_allocator" << endl;
		}
	};


}

namespace std
{
	// alias template, see http://en.cppreference.com/w/cpp/language/type_alias
	template <typename _Tp>
	using __self_allocator_base = __self_gnu_cxx::new_allocator<_Tp>;
}

namespace std
{
	template <typename _Tp>
	class self_allocator: public __self_allocator_base<_Tp>
	{

	};
}


int main()
{
	_self_GLIBCXX_VISIBILITY(default)
	_self_GLIBCXX_VISIBILITY(ok)

	std::self_allocator<int> alloc;

	return 0;
}
