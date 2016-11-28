//
// @file:           my_iterator_adapter.h
// @author:         cuckoo
// @date:           2016/11/22 16:12:09
// @description:    iterator adapter
// @note
//

#ifndef SGI_CHAPTER8_MY_ITERATOR_ADAPTER_H_
#define SGI_CHAPTER8_MY_ITERATOR_ADAPTER_H_

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

#include "Chapter3/iterator_traits_template.h"

// ======================================================================================
//
//            back_insert_iterator
//
// ======================================================================================

template <typename Container>
class BackInsertIterator
{
protected:
    Container *container_;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;

    explicit BackInsertIterator(Container &x) : container_(&x) { }

    BackInsertIterator & operator=(const typename Container::value_type &value)
    {
        container_->push_back(value);       // call push_back() of the container
        return *this;
    }
    BackInsertIterator & operator*() { return *this; }
    BackInsertIterator & operator++() { return *this; }
    BackInsertIterator & operator++(int) { return *this; }
};

template <typename Container>
inline BackInsertIterator<Container>
BackInserter(Container & x)
{
    return BackInsertIterator<Container>(x);
}

// ======================================================================================
//
//            front_insert_iterator
//
// ======================================================================================

template <typename Container>
class FrontInsertIterator
{
protected:
    Container *container_;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;

    explicit FrontInsertIterator(Container &x) : container_(x) { }

    FrontInsertIterator & operator=(typename Container::value_type &value)
    {
        container_->push_front(value);      // call push_front() of the container
        return *this;
    }
    FrontInsertIterator & operator*() { return *this; }
    FrontInsertIterator & operator++() { return *this; }
    FrontInsertIterator & operator++(int) { return *this; }
};

template <typename Container>
inline FrontInsertIterator<Container>
FrontInserter(Container &x)
{
    return FrontInsertIterator<Container>(x);
}

// ======================================================================================
//
//            insert_iterator
//
// ======================================================================================

template <typename Container>
class InsertIterator
{
protected:
    Container *container_;
    typename Container::iterator iter_;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;

    explicit InsertIterator(Container &x, typename Container::iterator i)
                : container_(x), iter_(i) { }

    InsertIterator & operator=(typename Container::value_type &value)
    {
        iter_ = container_->insert(iter_, value);      // call insert() of the container
        ++iter_;                                       // point to the original data
        return *this;
    }
    InsertIterator & operator*() { return *this; }
    InsertIterator & operator++() { return *this; }
    InsertIterator & operator++(int) { return *this; }
};

template <typename Container, typename Iterator>
inline InsertIterator<Container>
Inserter(Container &x, Iterator i)
{
    typename Container::iterator iter;
    return InsertIterator<Container>(x, iter(i));
}

// ======================================================================================
//
//            reverse iterator
//
// ======================================================================================

template <typename Iterator>
class ReverseIterator
{
protected:
    Iterator current;

public:
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::reference reference;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;

    typedef Iterator IteratorType;
    typedef ReverseIterator<Iterator> Self;

    ReverseIterator() { /*cout << "default constructor" << endl;*/ }
    explicit ReverseIterator(IteratorType x) : current(x) { }
    ReverseIterator(const Self &rhs) : current(rhs.current) { /*cout << "copy constructor" << endl;*/ }

    IteratorType base() const { return current; }

    reference operator*() const
    {
        IteratorType temp = current;
        return *--temp;
    }
    pointer operator->() const { return &(operator*()); }

    Self & operator++()
    {
        --current;
        return *this;
    }
    Self operator++(int)
    {
        Self temp = *this;
        --current;
        return temp;
    }
    Self & operator--()
    {
        ++current;
        return *this;
    }
    Self operator--(int)
    {
        Self temp = *this;
        ++current;
        return temp;
    }
    Self operator+(difference_type n) const
    {
        return Self(current - n);
    }
    Self & operator+=(difference_type n)
    {
        current -= n;
        return *this;
    }
    Self operator-(difference_type n) const
    {
        return Self(current + n);
    }
    Self & operator-=(difference_type n)
    {
        current += n;
        return *this;
    }
    reference operator[](difference_type n)
    {
        return *(*this + n);
    }
};

template <typename Iterator>
bool operator==(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}
template <typename Iterator>
bool operator!=(const ReverseIterator<Iterator> &lhs, const ReverseIterator<Iterator> &rhs)
{
    return !(lhs == rhs);
}


// ======================================================================================
//
//            stream iterator
//
// ======================================================================================

template <typename T>
class OstreamIterator
{
private:
    ostream *os_;
    const char *separator;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void reference;
    typedef void pointer;
    typedef void difference_type;

    OstreamIterator(ostream &os) : os_(&os), separator(0) { }
    OstreamIterator(ostream &os, const char *str) : os_(&os), separator(str) { }

    OstreamIterator<T> & operator=(const T &value)
    {
        *os_ << value;
        if(*separator)
            *os_ << separator;
        return *this;
    }

    OstreamIterator<T> & operator*() { return *this; }
    OstreamIterator<T> & operator++() { return *this; }
    OstreamIterator<T> & operator++(int) { return *this; }
};

template <typename T, typename Distance = ptrdiff_t>
class IstreamIterator
{
private:
    istream *is_;
    T value;
    bool end_marker_;

    void read()
    {
        end_marker_ = (is_ && *is_) ? true : false;
        if(end_marker_)
        {
            *is_ >> value;
            end_marker_ = (*is_) ? true : false;
        }
    }

public:
    typedef input_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef Distance difference_type;

    IstreamIterator() : is_(&cin), end_marker_(false) { }
    IstreamIterator(istream &is) : is_(&is) { read(); }

    reference operator*() const { return value; }
    pointer operator->() const { return &(operator*()); }

    IstreamIterator<T, Distance> & operator++()
    {
        read();
        return *this;
    }
    IstreamIterator<T, Distance> operator++(int)
    {
        IstreamIterator<T, Distance> temp = *this;
        ++*this;        // or read()
        return temp;
    }

    bool equal(const IstreamIterator<T, Distance> &rhs) const
    {
        return (end_marker_ == rhs.end_marker_) && (!end_marker_ || is_ == rhs.is_);
    }
};

template<typename T, typename Distance>
inline bool operator==(const IstreamIterator<T, Distance> &lhs, const IstreamIterator<T, Distance> &rhs)
{
    lhs.equal(rhs);
}
template<typename T, typename Distance>
inline bool operator!=(const IstreamIterator<T, Distance> &lhs, const IstreamIterator<T, Distance> &rhs)
{
    return !(lhs == rhs);
}

#endif
