#include <iostream>

using namespace std;

/*
 * The task is to implement function that finds ids of all columns of matrix with maximum sum of elements.
 * This function should be implemented as a separate assembly module.
 */

extern "C" int transpose(int* a, int n, int m);

void print(int *a, int n, int m)
{
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cout << a[m * i + j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int c[100] = {1, 4, 98,
	              3, 1000, 9};
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> c[i * m + j];
		}
	}
	transpose(c, 2, 3);
	print(c, 3, 2);
	return 0;
}
