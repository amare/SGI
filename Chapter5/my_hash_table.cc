//
// @file:           my_hash_table.cc
// @author:         cuckoo
// @date:           2016/11/17 20:56:44
// @description:    test code for my_hash_table
// @note
//

#include "my_hash_table.h"

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
using std::_Identity;
using std::equal_to;

#include <vector>
using std::vector;

#include "stl_hash_fun.h"

int main()
{
	HashTable<int, int, hash<int>, _Identity<int>, equal_to<int> >
		my_hash_tab(50, hash<int>(), equal_to<int>());

    cout << "Max bucket count: " << my_hash_tab.MaxBucketCount() << endl;
	cout << "Current bucket count: " << my_hash_tab.BucketCount() << endl;
	cout << "Number of elements: " << my_hash_tab.number_of_elements() << endl;

    my_hash_tab.InsertUnique(59);
    my_hash_tab.InsertUnique(63);
    my_hash_tab.InsertUnique(108);
    my_hash_tab.InsertUnique(2);
    my_hash_tab.InsertUnique(53);
    my_hash_tab.InsertUnique(55);
    cout << "Current bucket count: " << my_hash_tab.BucketCount() << endl;
    cout << "Number of elements: " << my_hash_tab.number_of_elements() << endl;
    for(auto iter = my_hash_tab.begin(); iter != my_hash_tab.end(); ++iter)
        cout << *iter << " ";
    cout << endl;

    for(int i = 0; i < my_hash_tab.BucketCount(); ++i)
    {
        int n = my_hash_tab.elems_in_bucket(i);
        if(n != 0)
            cout << "bucket[" << i << "] has " << n << " elements." << endl;
    }

    for(int i = 0; i <= 47; ++i)
        my_hash_tab.InsertEqual(i);
    cout << "Current bucket count: " << my_hash_tab.BucketCount() << endl;
    cout << "Number of elements: " << my_hash_tab.number_of_elements() << endl;

    for(int i = 0; i < my_hash_tab.BucketCount(); ++i)
    {
        int n = my_hash_tab.elems_in_bucket(i);
        if(n != 0)
            cout << "bucket[" << i << "] has " << n << " elements." << endl;
    }

    for(auto iter = my_hash_tab.begin(); iter != my_hash_tab.end(); ++iter)
        cout << *iter << " ";
    cout << endl;

    auto find_iter = my_hash_tab.find(190);
    if(find_iter != my_hash_tab.end())
        cout << *find_iter << endl;

    cout << my_hash_tab.count(2) << endl;

/*
    cout << "====== test code for <const ValueType&> ======" << endl;
    int original_int = 4;
    const int & const_reference_int = original_int;
    cout << "====== const_reference_int is initialized to original_int(4) ======" << endl;
    cout << "const_reference_int: " << const_reference_int << endl;
    // const_reference_int = 5;     //@gps: wrong grammar
    original_int = 5;
    cout << "====== original_int is reset to 5 ======" << endl;
    cout << "const_reference_int: " << const_reference_int << endl;
*/

	return 0;
}
