//
// @file:           my_numeric.h
// @author:         cuckoo
// @date:           2016/12/30 16:41:02
// @description:    implementation of my numeric algorithm
// @note
//

#ifndef SGI_CHAPTER6_MY_NUMERIC_H_
#define SGI_CHAPTER6_MY_NUMERIC_H_

#include <functional>
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;

#include "Chapter3/iterator_traits_template.h"

namespace gps
{

// accumulate
template <typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init)
{
    for(; first != last; ++first)
    {
        init += *first;
    }
    return init;
}
template <typename InputIterator, typename T, typename BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op)
{
    for(; first != last; ++first)
    {
        init = op(init, *first);
    }
    return init;
}

// InnerProduct
template <typename InputIterator1, typename InputIterator2, typename T>
T InnerProduct(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        init += *first1 * *first2;
    }
    return init;
}
template <typename InputIterator1, typename InputIterator2, typename T,
    typename BinaryOperation1, typename BinaryOperation2>
T InnerProduct(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
        BinaryOperation1 op1, BinaryOperation2 op2)
{
    for(; first1 != last1; ++first1, ++first2)
    {
        init = op1(init, op2(*first1, *first2));
    }
    return init;
}

//PartialSum
template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator PartialSumAux(InputIterator first, InputIterator last, OutputIterator result,
        T*)
{
    T value = *first;
    while(++first != last)
    {
        value += *first;
        *++result = value;
    }
    return ++result;
}
template <typename InputIterator, typename OutputIterator>
OutputIterator PartialSum(InputIterator first, InputIterator last, OutputIterator result)
{
    if(first == last)
    {
        return result;
    }
    *result = *first;
    return PartialSumAux(first, last, result, value_type(first));
}
template <typename InputIterator, typename OutputIterator, typename T,
    typename BinaryOperation>
OutputIterator PartialSumAux(InputIterator first, InputIterator last, OutputIterator result,
        T*, BinaryOperation op)
{
    T value = *first;
    while(++first != last)
    {
        value = op(value, *first);
        *++result = value;
    }
    return ++result;
}
template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator PartialSum(InputIterator first, InputIterator last,
        OutputIterator result, BinaryOperation op)
{
    if(first == last)
    {
        return result;
    }
    *result = *first;
    return PartialSumAux(first, last, result, value_type(first), op);
}

//AdjacentDifference
template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator AdjacentDifferenceAux(InputIterator first, InputIterator last,
        OutputIterator result, T*)
{
    T value = *first;
    while(++first != last)
    {
        T temp = *first;
        *++result = temp - value;
        value = temp;
    }
    return ++result;
}
template <typename InputIterator, typename OutputIterator>
OutputIterator AdjacentDifference(InputIterator first, InputIterator last,
        OutputIterator result)
{
    if(first == last)
    {
        return result;
    }
    *result = *first;
    return AdjacentDifferenceAux(first, last, result, value_type(first));
}

template <typename InputIterator, typename OutputIterator, typename T,
        typename BinaryOperation>
OutputIterator AdjacentDifferenceAux(InputIterator first, InputIterator last,
        OutputIterator result, T*, BinaryOperation op)
{
    T value = *first;
    while(++first != last)
    {
        T temp = *first;
        *++result = op(temp, value);
        value = temp;
    }
    return ++result;
}
template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator AdjacentDifference(InputIterator first, InputIterator last,
        OutputIterator result, BinaryOperation op)
{
    if(first == last)
    {
        return result;
    }
    *result = *first;
    return AdjacentDifferenceAux(first, last, result, value_type(first), op);
}

// power
template <typename T>
inline T identity_element(plus<T>)
{
    return T(0);
}
template <typename T>
inline T identity_element(minus<T>)
{
    return T(0);
}
template <typename T>
inline T identity_element(multiplies<T>)
{
    return T(1);
}
template <typename T>
inline T identity_element(divides<T>)
{
    return T(1);
}

template <typename T, typename Integer, typename MonoidOperation>
T power(T x, Integer n, MonoidOperation op)
{
    if(n == 0)
    {
        return identity_element(op);
    }
    else
    {
        /* normal verison*/
/*
        T result = x;
        while(--n)
        {
            result = op(x, result);
        }
        return result;
*/
        /*SGI version*/
        while((n & 1) == 0)
        {
            x = op(x, x);
            n >>= 1;
        }
        T result2 = x;
        n >>= 1;
        while(n != 0)
        {
            x = op(x, x);
            if((n & 1) != 0)
            {
                result2 = op(result2, x);
            }
            n >>= 1;
        }
        return result2;
    }
}
template<typename T, typename Integer>
T power(T x, Integer n)
{
    return power(x, n, multiplies<int>());
}

// iota
template <typename InputIterator, typename T>
void itoa(InputIterator first, InputIterator last, T n)
{
    while(first != last)
    {
        *first++ = n++;
    }
}

} // namespace gps
#endif
