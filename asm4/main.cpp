#include <iostream>
#include <bitset>

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

void transpose1(int *a, int n, int m)
{
	char *used = (char*)malloc(n * m);
	int i;
	for(i = 0; i < n * m; ++i) {
		used[i] = 0;
	}
	for(i = 1; i < n * m - 1; ++i) {
		if(!used[i]) {
			int tmp = a[i];
			int id = (n * i) % (n * m - 1);
			printf("id: %d %d\n", id, i);
			a[i] = a[id];
			a[id] = tmp;
			used[i] = 1;
			used[id] = 1;
		}
	}
}

// Non-square matrix transpose of matrix of size r x c and base address A
void transpose2(int *A, int r, int c)
{
    int size = r*c - 1;
    int t; // holds element to be replaced, eventually becomes next element to move
    int next; // location of 't' to be moved
    int cycleBegin; // holds start of cycle
    int i; // iterator
    bitset<128> b; // hash to mark moved elements

    b.reset();
    b[0] = b[size] = 1;
    i = 1; // Note that A[0] and A[size-1] won't move
    while (i < size)
    {
        cycleBegin = i;
        t = A[i];
        do
        {
            // Input matrix [r x c]
            // Output matrix 1
            // i_new = (i*r)%(N-1)
            next = (i*r)%size;
            swap(A[next], t);
            b[i] = 1;
            i = next;
        }
        while (i != cycleBegin);

        // Get Next Move (what about querying random location?)
        for (i = 1; i < size && b[i]; i++)
            ;
    }
}

int main()
{
	int c[9] = {1, 4, 98,
	            3, 1000, 9};
	transpose(c, 2, 3);
	print(c, 3, 2);
	return 0;
}
