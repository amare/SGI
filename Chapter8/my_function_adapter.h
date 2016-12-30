//
// @file:           my_function_adapter.h
// @author:         cuckoo
// @date:           2016/11/28 15:05:05
// @description:    8.4 in Annotated STL Source
// @note
//

#ifndef SGI_CHAPTER8_MY_FUNCTION_ADAPTER_H_
#define SGI_CHAPTER8_MY_FUNCTION_ADAPTER_H_

namespace gps
{

template <typename Argument, typename Result>
struct unary_function
{
    typedef Argument argument_type;
    typedef Result result_type;
};

template <typename Argument1, typename Argument2, typename Result>
struct binary_function
{
    typedef Argument1 first_argument_type;
    typedef Argument2 second_argument_type;
    typedef Result result_type;
};

// ======================================================================================
//
//            not1
//
// ======================================================================================
template <typename Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type, bool>
{
protected:
    Predicate predicate_;

public:
    explicit unary_negate(const Predicate &pred) : predicate_(pred) { }
    bool operator()(const typename Predicate::argument_type &arg) const
    {
        return !predicate_(arg);
    }
};
template <typename Predicate>
inline unary_negate<Predicate> not1(const Predicate &pred)
{
    return unary_negate<Predicate>(pred);
}

// ======================================================================================
//
//            not2
//
// ======================================================================================
template <typename Predicate>
class binary_negate : public binary_function<typename Predicate::first_argument_type,
                                             typename Predicate::second_argument_type,
                                             bool>
{
protected:
    Predicate predicate_;

public:
    explicit binary_negate(const Predicate &pred) : predicate_(pred) { }
    bool operator()(const typename Predicate::first_argument_type &arg1,
                    const typename Predicate::second_argument_type &arg2) const
    {
        return !predicate_(arg1, arg2);
    }
};
template <typename Predicate>
inline binary_negate<Predicate> not2(const Predicate &pred)
{
    return binary_negate<Predicate>(pred);
}

// ======================================================================================
//
//            bind1st
//
// ======================================================================================
template <typename Operation>
class binder1st : public unary_function<typename Operation::second_argument_type,
                                        typename Operation::result_type>
{
protected:
    Operation operation_;
    typename Operation::first_argument_type argument1;

public:
    binder1st(const Operation &oper,
              const typename Operation::first_argument_type &arg1)
        : operation_(oper), argument1(arg1) { }

    typename Operation::result_type
    operator()(const typename Operation::second_argument_type &arg2) const
    {
        return operation_(argument1, arg2);
    }
};
template <typename Operation, typename T>
inline binder1st<Operation> bind1st(const Operation &oper,
                                    const T &arg1)
{
    typedef typename Operation::first_argument_type Argument1;
    return binder1st<Operation>(oper, Argument1(arg1));
}

// ======================================================================================
//
//            bind2nd
//
// ======================================================================================
template <typename Operation>
class binder2nd : public unary_function<typename Operation::first_argument_type,
                                        typename Operation::result_type>
{
protected:
    Operation operation_;
    typename Operation::second_argument_type argument2;

public:
    binder2nd(const Operation &oper,
              const typename Operation::second_argument_type &arg2)
        : operation_(oper), argument2(arg2) { }

    typename Operation::result_type
    operator()(const typename Operation::first_argument_type &arg1) const
    {
        return operation_(arg1, argument2);
    }
};
template <typename Operation, typename T>
inline binder2nd<Operation> bind2nd(const Operation &oper,
                                    const T &arg2)
{
    typedef typename Operation::second_argument_type Argument2;
    return binder2nd<Operation>(oper, Argument2(arg2));
}

// ======================================================================================
//
//            compose1: h(x) = f(g(x));
//
// ======================================================================================
template <typename Operation1, typename Operation2>
class unary_compose : public unary_function<typename Operation2::argument_type,
                                            typename Operation1::result_type>
{
protected:
    Operation1 operation1_;
    Operation2 operation2_;

public:
    unary_compose(const Operation1 &oper1, const Operation2 &oper2)
        : operation1_(oper1), operation2_(oper2) { }

    typename Operation1::result_type
    operator()(const typename Operation2::argument_type &arg)
    {
        return operation1_(operation2_(arg));
    }
};
template <typename Operation1, typename Operation2>
inline unary_compose<Operation1, Operation2>
compose1(const Operation1 &oper1, const Operation2 &oper2)
{
    return unary_compose<Operation1, Operation2>(oper1, oper2);
}

// ======================================================================================
//
//            compose2: h(x) = f(g1(x), g2(x));
//
// ======================================================================================
template <typename Operation1, typename Operation2, typename Operation3>
class binary_compose : public unary_function<typename Operation2::argument_type,
                                             typename Operation1::result_type>
{
protected:
    Operation1 operation1_;
    Operation2 operation2_;
    Operation3 operation3_;

public:
    binary_compose(const Operation1 &oper1, const Operation2 &oper2,
                   const Operation3 &oper3)
        : operation1_(oper1), operation2_(oper2), operation3_(oper3) { }

    typename Operation1::result_type
    operator()(const typename Operation2::argument_type &arg) const
    {
        return operation1_(operation2_(arg), operation3_(arg));
    }
};
template <typename Operation1, typename Operation2, typename Operation3>
inline binary_compose<Operation1, Operation2, Operation3>
compose2(const Operation1 &oper1, const Operation2 &oper2, const Operation3 &oper3)
{
    return binary_compose<Operation1, Operation2, Operation3>(oper1, oper2, oper3);
}

// ======================================================================================
//
//            ptr_fun
//
// ======================================================================================
template <typename Argument, typename Result>
class pointer_to_unary_function : public unary_function<Argument, Result>
{
protected:
    Result (*ptr_)(Argument);

public:
    pointer_to_unary_function() { }
    explicit pointer_to_unary_function(Result (*x)(Argument)) : ptr_(x) { }

    Result operator()(Argument arg) const { return ptr_(arg); }
};
template <typename Argument, typename Result>
inline pointer_to_unary_function<Argument, Result>
ptr_fun(Result (*x)(Argument))
{
    return pointer_to_unary_function<Argument, Result>(x);
}

template <typename Argument1, typename Argument2, typename Result>
class pointer_to_binary_function : public binary_function<Argument1, Argument2, Result>
{
protected:
    Result (*ptr_)(Argument1, Argument2);

public:
    pointer_to_binary_function() { }
    explicit pointer_to_binary_function(Result (*x)(Argument1, Argument2)) : ptr_(x) { }

    Result operator()(Argument1 arg1, Argument2 arg2) const { return ptr_(arg1, arg2); }
};
template <typename Argument1, typename Argument2, typename Result>
inline pointer_to_binary_function<Argument1, Argument2, Result>
ptr_fun(Result (*x)(Argument1, Argument2))
{
    return pointer_to_binary_function<Argument1, Argument2, Result>(x);
}

} // namespace gps


#endif
