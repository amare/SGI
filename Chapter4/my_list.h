//
// @file:           my_list.h
// @author:         cuckoo
// @date:           2016/10/30 19:18:13
// @description:    /*info*/
// @note
//

#ifndef SGI_CHAPTER4_MY_LIST_H_
#define SGI_CHAPTER4_MY_LIST_H_

#include "Chapter2/my_construct.h"

#include <cstddef>		// for ptrdiff_t, size_t
#include <bits/stl_iterator_base_types.h>		// for std::bidirectional_iterator_tag

#include <new>
#include <iostream>
using std::cout;
using std::endl;

#include "Chapter2/default_malloc_template.h"

template <typename T>
struct ListNode
{
	ListNode<T> *  prev;
	ListNode<T> *  next;
	T              data;
};

template <typename T>
struct ListIterator
{
	typedef T                                value_type;
	typedef T*                               pointer;
	typedef T&                               reference;
	typedef ptrdiff_t                        difference_type;
	typedef std::bidirectional_iterator_tag  iterator_category;

	typedef ListNode<T>* list_node_ptr;
	typedef ListIterator<T> SELF;

	// constructor
	ListIterator() { }
	ListIterator(list_node_ptr node): node_(node) { }

	// operator
	bool operator==(const SELF& rhs) const
	{
		return node_ == rhs.node_;
	}
	bool operator!=(const SELF& rhs) const
	{
		return !(*this == rhs);
	}

	reference operator*() const
	{
		return node_->data;
	}
	pointer operator->() const
	{
		return & this->operator*();
	}

	SELF& operator++()
	{
		node_ = node_->next;
		return *this;
	}
	SELF operator++(int)
	{
		SELF temp = *this;
		++*this;
		return temp;
	}

	SELF& operator--()
	{
		node_ = node_->prev;
		return *this;
	}
	SELF operator--(int)
	{
		SELF temp = *this;
		--*this;
		return temp;
	}

	list_node_ptr node_;		// the only member points to %list element
};


template <typename T, typename Alloc>
class SimpleAlloc
{
public:
	static T* allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n*sizeof(T));
	}
	static T* allocate(void)
	{
		return (T*)Alloc::allocate(sizeof(T));
	}
	static void deallocate(T *p, size_t n)
	{
		if(0 != n)
		{
			Alloc::deallocate(p, n*sizeof(T));
		}
	}
	static void deallocate(T *p)
	{
		Alloc::deallocate(p, sizeof(T));
	}
};

typedef __default_malloc_template<false, 0> alloc;

template <typename T, typename Alloc = alloc>
class MyList
{
public:
	typedef ListIterator<T> iterator;
	typedef T& reference;
	typedef size_t size_type;

	typedef ListNode<T> list_node;
	typedef list_node* list_node_ptr;
	typedef SimpleAlloc<list_node, Alloc> list_node_allocator;

	// constructor
	MyList()
	{
		EmptyInitialize();
	}


	// member function
	iterator begin()
	{
		return blank_node->next;		// compiler will auto transfer list_node_ptr to iterator
								// see p264, Primer
	}
	iterator end()
	{
		return blank_node;
	}
	bool empty() const
	{
		return blank_node->next == blank_node;
	}
	size_type size() const
	{
		size_type ret = distance(blank_node->next, blank_node);
		return ret;
	}
	reference front()
	{
		return *begin();
	}
	reference back()
	{
		return *--end();
	}

	void push_back(const T& x)
	{
		insert(end(), x);
	}
	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	void pop_back()
	{
		iterator temp = end();
		erase(--temp);
	}
	void pop_front()
	{
		erase(begin());
	}

	void clear()
	{
		cout << "====== call clear() =======" << endl;
		list_node_ptr cur = blank_node->next;
		list_node_ptr temp;
		while(cur != blank_node)
		{
			temp = cur;
			cur = cur->next;
			destroy_node(temp);
		}

		blank_node->next = blank_node;
		blank_node->prev = blank_node;
	}

	void remove(const T& x)
	{
		cout << "====== call remove(" << x << ") ======" << endl;
		iterator first = begin();
		iterator last = end();
		iterator temp;
		while(first != last)
		{
			temp = first;
			++temp;
			if(*first == x) erase(first);
			first = temp;
		}
	}

	iterator insert(iterator position, const T& x)
	{
		cout << "====== call insert() ======" << endl;
		list_node_ptr temp = create_node(x);
		temp->next = position.node_;
		temp->prev = position.node_->prev;
		position.node_->prev->next = temp;
		position.node_->prev = temp;

		return temp;
	}

	// erase node to which iterator points
	iterator erase(iterator position)
	{
		list_node_ptr next_node = position.node_->next;
		next_node->prev = position.node_->prev;
		position.node_->prev->next = next_node;

		destroy_node(position.node_);

		return next_node;
	}

protected:
	// tool function
	static size_t distance(list_node_ptr first, list_node_ptr last)
	{
		size_t count = 0;
		while(first != last)
		{
			++count;
			first = first->next;
		}
		return count;
	}
	list_node_ptr get_node()
	{
		return list_node_allocator::allocate();
	}
	void put_node(list_node_ptr p)
	{
		list_node_allocator::deallocate(p);
	}
	list_node_ptr create_node(const T& x)
	{
		list_node_ptr p = get_node();
		construct(&p->data, x);
		return p;
	}
	void destroy_node(list_node_ptr p)
	{
		destroy(&p->data);
		put_node(p);
	}
	void EmptyInitialize()
	{
		blank_node = get_node();
		blank_node->next = blank_node;
		blank_node->prev = blank_node;
	}


private:
	list_node_ptr blank_node;		// points to a blank node at the end of list
};


#endif
