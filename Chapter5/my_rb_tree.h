//
// @file:           my_rb_tree.h
// @author:         cuckoo
// @date:           2016/11/15 17:03:06
// @description:    /*info*/
// @note
//

#ifndef SGI_CHAPTER5_MY_RB_TREE_H_
#define SGI_CHAPTER5_MY_RB_TREE_H_

#include <iostream>
using std::cout;
using std::endl;
#include <utility>
using std::pair;

#include "Chapter2/my_construct.h"
#include "Chapter2/default_malloc_template.h"

#define GPS_DEBUG_

typedef bool RBTreeColorType;
const RBTreeColorType kRBTreeColorRed = false;
const RBTreeColorType kRBTreeColorBlack = true;

struct RBTreeNodeBase
{
	typedef RBTreeColorType ColorType;
	typedef RBTreeNodeBase* BasePtr;

	ColorType color;
	BasePtr parent;
	BasePtr left;
	BasePtr right;

	static BasePtr Minimum(BasePtr node)
	{
		while(0 != node->left)
		{
			node = node->left;
		}
		return node;
	}

	static BasePtr Maximum(BasePtr node)
	{
		while(0 != node->right)
		{
			node = node->right;
		}
		return node;
	}
};

template <typename Value>
struct RBTreeNode : public RBTreeNodeBase
{
	Value value_field;
};

struct RBTreeIteratorBase
{
	typedef RBTreeNodeBase::BasePtr BasePtr;

	BasePtr node;

	// called by operator++
	void increment()
	{
	#if !defined(GPS_DEBUG_)
		cout << "====== increment() ======" << endl;
	#endif
		if(0 != node->right)					// has right child
		{
			node = node->right;
			while(node->left != 0)				// to the end of left child tree
			{
				node = node->left;
			}
		}
		else
		{										// has no right child
			BasePtr parent = node->parent;		// find parent
			while(node == parent->right)		// until node is the left child of its parent
			{
				node = parent;
				parent = parent->parent;		// or parent = node->parent
			}
			if(node->right != parent)			// see p218
			{
				node = parent;					// parent is the answer
			}
			// node->right == parent means that node is header and its parent is root, so operator++()
			// should return header
		#if !defined(GPS_DEBUG_)
			cout << "color: " << node->color << endl;
		#endif
		}
	}

	// called by operator--
	void decrement()
	{
		if(kRBTreeColorRed == node->color && node->parent->parent == node)		// node is header
		{
			node = node->right;
		}
		else if(0 != node->left)			// has left child
		{
			node = node->left;
			while(0 != node->right)			// to the end of right child tree
			{
				node = node->right;
			}
		}
		else
		{
			BasePtr parent = node->parent;
			while(node == parent->left)		// until node is the right child of its parent
			{
				node = parent;
				parent = parent->parent;	// or parent = node->parent
			}
			node = parent;					// parent is the answer
		}
	}
};

template <typename Value, typename Reference, typename Pointer>
struct RBTreeIterator : public RBTreeIteratorBase
{
	typedef Value     value_type;
	typedef Reference reference;
	typedef Pointer   pointer;
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;

	typedef bidirectional_iterator_tag iterator_category;
	typedef RBTreeIterator<Value, Value&, Value*> iterator;
	typedef RBTreeIterator<Value, const Value&, const Value*> const_iterator;
	typedef RBTreeIterator<Value, Reference, Pointer> self;

	typedef RBTreeNode<Value>* link_type;

	RBTreeIterator() { }
	RBTreeIterator(link_type x) { node = x; }
	RBTreeIterator(const iterator &iter) { node = iter.node; }

	reference operator*() const
	{
		return link_type(node)->value_field;		// node ???
	}
	pointer operator->() const
	{
		return &(operator*());
	}

	self & operator++()
	{
		increment();
		return *this;
	}
	self operator++(int)
	{
		self ret = *this;
		++*this;
		return ret;
	}
	self & operator--()
	{
		decrement();
		return *this;
	}
	self operator--(int)
	{
		self ret = *this;
		--*this;
		return ret;
	}
};

inline bool operator==(const RBTreeIteratorBase &lhs, const RBTreeIteratorBase &rhs)
{
	return lhs.node == rhs.node;
}
inline bool operator!=(const RBTreeIteratorBase &lhs, const RBTreeIteratorBase &rhs)
{
#if !defined(GPS_DEBUG_)
	cout << "====== operator!() =======" << endl;
	cout << lhs.node->color << " " << rhs.node->color << endl;
	cout << lhs.node << " " << rhs.node << endl;
#endif
	return !(lhs == rhs);
}

template <typename T, typename Alloc>
struct SimpleAlloc
{
	static T* allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}
	static T* allocate(void)
	{
		return (T*)Alloc::allocate(sizeof(T));
	}
	static void deallocate(T *p, size_t n)
	{
		if(0 != n)
		{
			Alloc::deallocate(p, n * sizeof(T));
		}
	}
	static void deallocate(T *p)
	{
		Alloc::deallocate(p, sizeof(T));
	}
};

// ======================================================================================
//
//			global function
//
// ======================================================================================

// left rotate
inline void RBTreeRotateLeft(RBTreeNodeBase *rotate_node, RBTreeNodeBase *& root)
{
#if defined(GPS_DEBUG_)
	cout << "\t=== RBTreeRotateLeft ===" << endl;
#endif
	RBTreeNodeBase *right_child = rotate_node->right;
	// right_child's left child and rotate_node
	rotate_node->right = right_child->left;
	if(0 != right_child->left)
		right_child->left->parent = rotate_node;

	// rotate_node's parent and right_child
	right_child->parent = rotate_node->parent;
	if(rotate_node == root)									// rotate node is the root
		root = right_child;
	else if(rotate_node == rotate_node->parent->left)		// is the left child of its parent
		rotate_node->parent->left = right_child;
	else 													// is the right child of its parent
		rotate_node->parent->right = right_child;

	// rotate_node and right_child
	right_child->left = rotate_node;
	rotate_node->parent = right_child;
}

// right rotate
inline void RBTreeRotateRight(RBTreeNodeBase *rotate_node, RBTreeNodeBase *& root)
{
#if defined(GPS_DEBUG_)
	cout << "\t=== RBTreeRotateRight ===" << endl;
#endif
	RBTreeNodeBase *left_child = rotate_node->left;
	// left_child's right child and rotate_node
	rotate_node->left = left_child->right;
	if(0 != left_child->right)
		left_child->right->parent = rotate_node;

	// rotate_node's parent and left_child
	left_child->parent = rotate_node->parent;
	if(rotate_node == root)
		root = left_child;
	else if(rotate_node == rotate_node->parent->right)
		rotate_node->parent->right = left_child;
	else
		rotate_node->parent->left = left_child;

	// roatate_node and left_child
	left_child->right = rotate_node;
	rotate_node->parent = left_child;
}

// rb-tree rebalance
inline void RBTreeRebalance(RBTreeNodeBase *new_node, RBTreeNodeBase *& root)
{
#if defined(GPS_DEBUG_)
	cout << "====== RBTreeRebalance ======" << endl;
#endif
	new_node->color = kRBTreeColorRed;
	while(new_node != root && new_node->parent->color == kRBTreeColorRed)
	{
		if(new_node->parent == new_node->parent->parent->left)
		{													// parent is the left child of the grandfather
			RBTreeNodeBase *right_uncle = new_node->parent->parent->right;
			if(right_uncle && right_uncle->color == kRBTreeColorRed)
			{												// right_uncle exists and it's color is red
				new_node->parent->color = kRBTreeColorBlack;
				right_uncle->color = kRBTreeColorBlack;
				new_node->parent->parent->color = kRBTreeColorRed;
				new_node = new_node->parent->parent;		// grandfather to be the new_node
			}
			else 					// no right_uncle or right_uncle's color is black
			{
				if(new_node == new_node->parent->right)
				{
					new_node = new_node->parent;			// parent to be the new_node
					RBTreeRotateLeft(new_node, root);
				}
				new_node->parent->color = kRBTreeColorBlack;
				new_node->parent->parent->color = kRBTreeColorRed;
				RBTreeRotateRight(new_node->parent->parent, root);
			}
		}
		else
		{													// parent is the right child of the grandfather
			RBTreeNodeBase *left_uncle = new_node->parent->parent->left;
			if(left_uncle && left_uncle->color == kRBTreeColorRed)
			{												// left_uncle exists and it's color is red
				new_node->parent->color = kRBTreeColorBlack;
				left_uncle->color = kRBTreeColorBlack;
				new_node->parent->parent->color = kRBTreeColorRed;
				new_node = new_node->parent->parent;		// grandfather to be the new_node
			}
			else 					// no left_uncle or left_uncle's color is black
			{
				if(new_node == new_node->parent->left)
				{
					new_node = new_node->parent;			// parent to be the new_node
					RBTreeRotateRight(new_node, root);
				}
				new_node->parent->color = kRBTreeColorBlack;
				new_node->parent->parent->color = kRBTreeColorRed;
				RBTreeRotateLeft(new_node->parent->parent, root);
			}
		}
	}// the end of while
	root->color = kRBTreeColorBlack;						// @gps: don't forget it!!!
}

// ======================================================================================
//
//			RB-Tree
//
// ======================================================================================

typedef __default_malloc_template<false, 0> alloc;

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
		  typename Alloc = alloc>
class RBTree
{
	typedef SimpleAlloc<RBTreeNode<Value>, Alloc> RBTreeNodeAllocator;

	typedef RBTreeNodeBase* BasePtr;
	typedef RBTreeNode<Value>* LinkType;
	typedef size_t SizeType;
	typedef RBTreeColorType ColorType;

	typedef Value ValueType;
	typedef Value& Reference;
	typedef Value* Pointer;


protected:
	LinkType GetNode() { return RBTreeNodeAllocator::allocate(); }
	void PutNode(LinkType node) { RBTreeNodeAllocator::deallocate(node); }

	LinkType CreateNode(const ValueType &v)
	{
		LinkType ret = GetNode();
		construct(&ret->value_field, v);
		return ret;
	}
	void DestroyNode(LinkType node)
	{
		destroy(&node->value_field);		// call destructor function
		PutNode(node);						// release memory
	}

protected:
	SizeType node_count_;
	LinkType header_;
	Compare key_compare_;

	LinkType & root() const { return (LinkType&)header_->parent; }
	LinkType & leftmost() const { return (LinkType&)header_->left; }
	LinkType & rightmost() const { return (LinkType&)header_->right; }

	static LinkType & left(LinkType node) { return (LinkType&)node->left; }
	static LinkType & right(LinkType node) { return (LinkType&)node->right; }
	static LinkType & Parent(LinkType node) { return (LinkType&)node->parent; }
	static Reference value(LinkType node) { return node->value_field; }
	static ColorType & color(LinkType node) { return (ColorType&)node->color; }
	static const Key & key(LinkType node) { return KeyOfValue()(value(node)); }

	static LinkType & left(BasePtr node) { return (LinkType&)node->left; }
	static LinkType & right(BasePtr node) { return (LinkType&)node->right; }
	static LinkType & Parent(BasePtr node) { return (LinkType&)node->parent; }
	static Reference value(BasePtr node) { return ((LinkType&)node)->value_field; }
	static ColorType & color(BasePtr node) { return (ColorType&)node->color; }
	static const Key & key(BasePtr node) { return KeyOfValue()(value((LinkType)node)); }

	static LinkType minimum(LinkType node) { return (LinkType)RBTreeNodeBase::Minimum(node); }
	static LinkType maximum(LinkType node) { return (LinkType)RBTreeNodeBase::Maximum(node); }

public:
	typedef RBTreeIterator<ValueType, Reference, Pointer> iterator;

public:
	iterator begin() { return leftmost(); }
	iterator end() { return header_; }
	bool empty() { return 0 == node_count_; }
	SizeType size() { return node_count_; }

	iterator insert_equal(const ValueType& value);
	pair<iterator, bool> insert_unique(const ValueType& value);
	iterator find(const Key& k);


private:
	iterator insert(BasePtr insert_node_, BasePtr parent_, const ValueType &value);
	void erase(LinkType node);
	void init()
	{
		header_ = GetNode();
		header_->color = kRBTreeColorRed;
		header_->parent = 0;
		header_->left = header_;
		header_->right = header_;
	}
	void clear()
	{
		if(0 != node_count_)
		{
			erase(root());
			header_->parent = 0;
			header_->left = header_;
			header_->right = header_;
			node_count_ = 0;
		}
	}

// ======================================================================================
//
//			constructor/destructor function
//
// ======================================================================================

public:
	RBTree(const Compare& comp = Compare()) : node_count_(0), key_compare_(comp) { init(); }
	~RBTree()
	{
	#if !defined(GPS_DEBUG_)
		cout << "====== ~RBTree() ======" << endl;
	#endif
		clear();
		PutNode(header_);
	}

};

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::erase(LinkType node)
{								// earse without rebalancing
	if(0 != node)
	{
	#if !defined(GPS_DEBUG_)
		cout << "====== erase() ======" << endl;
		cout << "node: " << node << endl;
	#endif
		erase(left(node));
		erase(right(node));
		DestroyNode(node);
	}
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
RBTree<Key, Value, KeyOfValue, Compare, Alloc>::
	insert(BasePtr insert_node_, BasePtr parent_, const ValueType& value)
{
	LinkType insert_node = (LinkType)insert_node_;
	LinkType parent = (LinkType)parent_;
	LinkType new_node;

	if(parent == header_ || insert_node != 0 /*??*/|| key_compare_(KeyOfValue()(value), key(parent)))
	{
		new_node = CreateNode(value);
		left(parent) = new_node;				// when parent is the header, leftmost() = new_node
		if(parent == header_)
		{
			root() = new_node;
			rightmost() = new_node;
		}
		else if(parent == leftmost())
			leftmost() = new_node;
	}
	else
	{
		new_node = CreateNode(value);
		right(parent) = new_node;
		if(parent == rightmost())
			rightmost() = new_node;
	}

	Parent(new_node) = parent;
	left(new_node) = 0;
	right(new_node) = 0;
										// the color of new_node is set in RBTreeRebalance() function
	RBTreeRebalance(new_node, header_->parent);
	++node_count_;

	return iterator(new_node);
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const ValueType& value)
{
	LinkType parent = header_;
	LinkType insert_node = root();

	while(0 != insert_node)
	{
		parent = insert_node;
		insert_node = key_compare_(KeyOfValue()(value), key(insert_node)) ?
														left(insert_node) : right(insert_node);
	}

	return insert(insert_node, parent, value);
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
pair<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const ValueType& value)
{
	LinkType parent = header_;
	LinkType insert_node = root();

	bool compare_result = true;
	while(0 != insert_node)
	{
		parent = insert_node;
		compare_result = key_compare_(KeyOfValue()(value), key(insert_node));
		insert_node = compare_result ? left(insert_node) : right(insert_node);
	}

	iterator parent_iterator = iterator(parent);
	if(compare_result)
	{
		if(parent_iterator == begin())			// parent is the leftmost()
			return pair<iterator, bool>(insert(insert_node, parent, value), true);
		else
			--parent_iterator;
	}
	if(key_compare_(key(parent_iterator.node), KeyOfValue()(value)))
		return pair<iterator, bool>(insert(insert_node, parent, value), true);

	return pair<iterator, bool>(parent_iterator, false);
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
RBTree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k)
{
	LinkType parent = header_;				// last node which is not less than k
	LinkType current_node = root();			// current node

	while(0 != current_node)
	{
		if(!key_compare_(key(current_node), k))
		{
			parent = current_node;
			current_node = left(current_node);
		}
		else
			current_node = right(current_node);
	}

	iterator result = iterator(parent);

	return (parent == end() || key_compare_(k, key(parent.node))) ? end() : result;
}

#endif
