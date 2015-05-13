#include <iostream>

using namespace std;

/*
 * The task is to implement function that finds ids of all columns of matrix with maximum sum of elements.
 * This function should be implemented as a separate assembly module.
 */

extern "C" int test1(int** a, int n, int m, int* ids, int* ids_num);

int main()
{
	int a, b;
	int c[] = {1, 4, 98,
	           3, 1000, 9000,
	           1, 2, 3};
	int ids[3];
	int ids_num;
	cout << test1((int**)c, 3, 3, ids, &ids_num) << endl;
	cout << ids_num << " " << ids[0] << endl;
	return 0;
}
