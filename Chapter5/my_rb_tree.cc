//
// @file:           rb_tree_test.cc
// @author:         cuckoo
// @date:           2016/11/15 16:39:33
// @description:    test code for rb-tree
// @note
//

#include "my_rb_tree.h"

#include <functional>
using std::less;
using std::_Identity;
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	RBTree<int, int, _Identity<int>, less<int> > my_tree;
	cout << my_tree.size() << endl;

	my_tree.insert_unique(10);
	my_tree.insert_unique(7);
	my_tree.insert_unique(8);
	my_tree.insert_unique(15);
	my_tree.insert_unique(5);
	my_tree.insert_unique(6);
	my_tree.insert_unique(11);
	my_tree.insert_unique(13);
	my_tree.insert_unique(12);

	for(auto iter = my_tree.begin(); iter != my_tree.end(); ++iter)
		cout << *iter << "(" << iter.node->color << ") ";
	cout << endl;

	cout << "=================================" << endl;
	auto result = my_tree.find(11);
	cout << *result << endl;

	return 0;
}
