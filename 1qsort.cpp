//
// @file:           1qsort.cpp
// @author:         cuckoo
// @date:           2016/10/06 13:25:44
// @description:    function pointer
// @note
//

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

int compare(const void *, const void *);

int main()
{
	int ia[10] = {32, 92, 57, 58, 10, 4, 25, 52, 59, 54};

	for(int i = 0; i < 10; ++i)
	{
		cout << ia[i] << ' ';
	}
	cout << endl;
	qsort(ia, sizeof(ia)/sizeof(int), sizeof(int), compare);
	cout << "====== after qsort ======" << endl;
	for(int i = 0; i < 10; ++i)
	{
		cout << ia[i] << ' ';
	}

	return 0;
}

int compare(const void *elem1, const void *elem2)
{
	const int *i1 = (const int *)elem1;
	const int *i2 = (const int *)elem2;

	if(*i1 < *i2)
		return -1;
	else if(*i1 == *i2)
		return 0;
	else
		return 1;
}
