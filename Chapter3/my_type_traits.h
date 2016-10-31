//
// @file:           my_type_traits.h
// @author:         cuckoo
// @date:           2016/10/31 20:14:24
// @description:    /*info*/
// @note
//

#ifndef SGI_CHAPTER3_MY_TYPE_TRAITS_H_
#define SGI_CHAPTER3_MY_TYPE_TRAITS_H_

struct TrueType { };
struct FalseType { };

template <typename Type>
struct TypeTraits
{
	typedef TrueType this_dummy_member_must_be_first;

	typedef FalseType has_trivial_default_constructor;
	typedef FalseType has_trivial_copy_constructor;
	typedef FalseType has_trivial_assignment_operator;
	typedef FalseType has_trivial_destructor;
	typedef FalseType is_POD_type;
};

template <>
struct TypeTraits<char>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<signed char>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<unsigned char>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<short>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<unsigned short>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<int>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<unsigned int>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<long>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<unsigned long>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<long long>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<unsigned long long>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<float>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<double>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <>
struct TypeTraits<long double>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

template <typename T>
struct TypeTraits<T*>
{
	typedef TrueType has_trivial_default_constructor;
	typedef TrueType has_trivial_copy_constructor;
	typedef TrueType has_trivial_assignment_operator;
	typedef TrueType has_trivial_destructor;
	typedef TrueType is_POD_type;
};

#endif
