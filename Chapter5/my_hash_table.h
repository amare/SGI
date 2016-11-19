//
// @file:           my_hash_table.h
// @author:         cuckoo
// @date:           2016/11/17 17:07:28
// @description:    /*info*/
// @note
//

#ifndef SGI_CHAPTER5_MY_HASH_TABLE_H_
#define SGI_CHAPTER5_MY_HASH_TABLE_H_

#include <cstddef>		// for ptrdiff_t, size_t


#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::lower_bound;

#include <utility>
using std::pair;


#include "Chapter2/my_construct.h"
#include "Chapter2/default_malloc_template.h"

#define GPS_DEBUG_

template <typename Value>
struct HashTableNode
{
	HashTableNode *next;
	Value value;
};

template <typename T, typename Alloc>
struct SimpleAlloc
{
	static T * allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}
	static T * allocate(void)
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

typedef __default_malloc_template<false, 0> alloc;

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc = alloc>
class HashTable;

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
struct HashTableIterator
{
	typedef Value      value_type;
	typedef Value&     Reference;
	typedef Value*     Pointer;
	typedef size_t     size_type;
	typedef ptrdiff_t  difference_type;

	typedef forward_iterator_tag iterator_category;

	typedef HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> HashTable;
	typedef HashTableNode<Value> Node;

	Node *current;
	HashTable *hash_table;

	// constructor
	HashTableIterator() { }
	HashTableIterator(Node *cur, HashTable *ht) : current(cur), hash_table(ht) { }
    HashTableIterator(const HashTableIterator &it) : current(it.current), hash_table(it.hash_table) { }

	// operator overloading
	Reference operator*() const { return current->value; }
	Pointer operator->() const { return &(operator*()); }
	iterator & operator++();
	iterator operator++(int);
};

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
          typename EqualKey, typename Alloc>
HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> &
HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++()
{
    Node *old = current;
    current = current->next;
    if(!current)
    {
        size_type bucket_index = hash_table->BucketNumber(old->value);
        while(!current && ++bucket_index < hash_table->buckets_.size())
        {
            current = hash_table->buckets_[bucket_index];
        }
    }

    return *this;
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
          typename EqualKey, typename Alloc>
HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>
HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++(int)
{
    HashTableIterator ret = *this;
    ++*this;
    return ret;
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
inline bool operator==(const HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> &lhs,
	const HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> &rhs)
{
	return lhs.current == rhs.current;
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
inline bool operator!=(const HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> &lhs,
	const HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> &rhs)
{
	return !(lhs == rhs);
}

// ======================================================================================
//
//			global variable and function
//
// ======================================================================================

static const int kNumPrimes = 28;
static const unsigned long kPrimerList[kNumPrimes] =
{
	53,         97,           193,        389,       769,
	1543,       3079,         6151,       12289,     24593,
	49157,      98317,        196613,     393241,    786433,
	1572869,    3145739,      6291469,    12582917,  25165843,
	50331653,   100663319,    201326611,  402653189, 805306457,
	1610612741, 3221225473ul, 429496729ul
};
inline unsigned long NextPrime(unsigned long n)
{
	const unsigned long *first = kPrimerList;
	const unsigned long *last = kPrimerList + kNumPrimes;
	const unsigned long *position = lower_bound(first, last, n);

	return position == last ? *(last - 1) : *position;
}

// ======================================================================================
//
//			HashTable
//
// ======================================================================================

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
class HashTable
{
public:
	typedef size_t SizeType;
	typedef Value ValueType;
	typedef Key KeyType;

	typedef HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;

friend struct HashTableIterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

public:
	SizeType number_of_elements() const { return number_of_elements_; }
	SizeType BucketCount() const { return buckets_.size(); }
	SizeType MaxBucketCount() const { return kPrimerList[kNumPrimes - 1]; }
	pair<iterator, bool> InsertUnique(const ValueType &obj)
	{
		Resize(number_of_elements_ + 1);
		InsertUniqueNoResize(obj);
	}
    iterator InsertEqual(const ValueType &obj)
    {
        Resize(number_of_elements_ + 1);
        InsertEqualNoResize(obj);
    }
    void Clear();
    iterator end() { return iterator(0, this); }
    iterator begin()
    {
        for(SizeType bucket_index = 0; bucket_index < buckets_.size(); ++bucket_index)
        {
            if(buckets_[bucket_index] != 0)
            {
                return iterator(buckets_[bucket_index], this);
            }
        }
        return end();
    }
    SizeType elems_in_bucket(SizeType bucket_index)
    {
        Node *current = buckets_[bucket_index];
        SizeType count = 0;
        while(current != 0)
        {
            ++count;
            current = current->next;
        }

        return count;
    }

    iterator find(const KeyType &key)
    {
        SizeType bucket_index = BucketNumberKey(key);
        Node *current = buckets_[bucket_index];
        while(current && !equals_(get_key_(current->value), key))
            current = current->next;

        return iterator(current, this);
    }

    SizeType count(const KeyType &key) const
    {
        SizeType result = 0;

        SizeType bucket_index = BucketNumberKey(key);
        Node *current = buckets_[bucket_index];
        while(current != 0)
        {
            if(equals_(get_key_(current->value), key))
                ++result;
            current = current->next;
        }

        return result;
    }
// ======================================================================================
//
//            private data
//
// ======================================================================================

private:
	HashFcn hash_;
	EqualKey equals_;
	ExtractKey get_key_;

	typedef HashTableNode<Value> Node;
	typedef SimpleAlloc<Node, Alloc> HashTableNodeAllocator;
	vector<Node*> buckets_;			// default space allocator
	SizeType number_of_elements_;

// ======================================================================================
//
//            constrctor/destructor
//
// ======================================================================================

public:
	HashTable(SizeType n, const HashFcn &hf, const EqualKey& eql) :
		hash_(hf), equals_(eql), get_key_(ExtractKey()), number_of_elements_(0)
	{
		InitializeBuckets(n);
	}
    ~HashTable() { Clear(); }

protected:
	Node * CreateNode(const ValueType &obj)
	{
		Node *ret = HashTableNodeAllocator::allocate();
		ret->next = 0;
		construct(&ret->value, obj);

		return ret;
	}
	void DestroyNode(Node *node)
	{
		destroy(&node->value);
		HashTableNodeAllocator::deallocate(node);
	}

	SizeType NextSize(SizeType n) const { return NextPrime(n); }
	void InitializeBuckets(SizeType n)
	{
		const SizeType number_of_bucket = NextSize(n);
	#if !defined(GPS_DEBUG_)
		cout << number_of_bucket << endl;
	#endif
		buckets_.reserve(number_of_bucket);
		buckets_.insert(buckets_.end(), number_of_bucket, static_cast<Node*>(0));
		number_of_elements_ = 0;
	}

	void Resize(SizeType num_elements_hint);
	pair<iterator, bool> InsertUniqueNoResize(const ValueType &obj);
    iterator InsertEqualNoResize(const ValueType &obj);

	SizeType BucketNumberKey(const KeyType &key, SizeType n) const
	{
		return hash_(key) % n;
	}
	SizeType BucketNumberKey(const KeyType &key) const
	{
		return BucketNumberKey(key, buckets_.size());
	}
	SizeType BucketNumber(const ValueType &obj) const
	{
		return BucketNumberKey(get_key_(obj));
	}
	SizeType BucketNumber(const ValueType &obj, SizeType n) const
	{
		return BucketNumberKey(get_key_(obj), n);
	}
};

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
void HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::Resize(SizeType num_elements_hint)
{
	const SizeType old_num_of_bucket = buckets_.size();
	if(num_elements_hint > old_num_of_bucket)
	{
		const SizeType new_num_of_bucket = NextSize(num_elements_hint);
		if( new_num_of_bucket > old_num_of_bucket)
		{
			vector<Node*> temp(new_num_of_bucket, static_cast<Node*>(0));
			for(SizeType old_bucket_index = 0; old_bucket_index < old_num_of_bucket; ++old_bucket_index)
			{
				Node *first = buckets_[old_bucket_index];
				while(first)
				{
					SizeType new_bucket_index = BucketNumber(first->value, new_num_of_bucket);

					buckets_[old_bucket_index] = first->next;
					first->next = temp[new_bucket_index];
					temp[new_bucket_index] = first;
					first = buckets_[old_bucket_index];
				}
			}// for
			buckets_.swap(temp);
		}// if
	}// if
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
		  typename EqualKey, typename Alloc>
pair<typename HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator, bool>
HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::InsertUniqueNoResize(const ValueType &obj)
{
	const SizeType bucket_index = BucketNumber(obj);
#if !defined(GPS_DEBUG_)
    cout << obj << "(" << bucket_index << ")" << endl;
#endif
	Node *first = buckets_[bucket_index];

	for(Node *current = first; current; current = current->next)
	{
		if(equals_(get_key_(current->value), get_key_(obj)))      // equal to some element
		{
			return pair<iterator, bool>(iterator(current, this), false);
		}
	}

	Node *new_node = CreateNode(obj);
	new_node->next = first;
	buckets_[bucket_index] = new_node;         // new_node insert to the head of list
	++number_of_elements_;                     // number of all elements increases

	return pair<iterator, bool>(iterator(new_node, this), true);
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
          typename EqualKey, typename Alloc>
typename HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator
HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::InsertEqualNoResize(const ValueType &obj)
{
    const SizeType bucket_index = BucketNumber(obj);
    Node *first = buckets_[bucket_index];

    for(Node *current = first; current; current = current->next)
    {
        if(equals_(get_key_(current->value), get_key_(obj)))        // equal to some element
        {
            Node *new_node = CreateNode(obj);
            new_node->next = current->next;
            current->next = new_node;
            ++number_of_elements_;

            return iterator(new_node, this);
        }
    }

    Node *new_node = CreateNode(obj);
    new_node->next = first;
    buckets_[bucket_index] = new_node;
    ++number_of_elements_;

    return iterator(new_node, this);
}

template <typename Value, typename Key, typename HashFcn, typename ExtractKey,
          typename EqualKey, typename Alloc>
void HashTable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::Clear()
{
    for(SizeType bucket_index = 0; bucket_index < buckets_.size(); ++ bucket_index)
    {
        Node *current = buckets_[bucket_index];
        while(current != 0)
        {
            Node *next_node = current->next;
            DestroyNode(current);
            current = next_node;
        }
        buckets_[bucket_index] = static_cast<Node*>(0);
    }
    number_of_elements_ = 0;
}

#endif
