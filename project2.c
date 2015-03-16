// LAOLU PETERS
// login: peterso
// ECE 368 
// SPRING 2015


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define CUTOFF 10
#define length(x) ( sizeof x / sizeof *x )


int main(void)
{

return 0;

}

struct pivots {
	int left, right;
	};
void swap ( int *a, int *b );
void insertion_sort ( int list[], int left, int right );
int median ( int list[], int left, int right );
struct pivots partition ( int list[], int left, int right );
void quicksort_r ( int list[], int left, int right );
void quicksort ( int list[], int n);


void swap ( int *a, int *b )
{
	int save = *a;
	*a = *b;
	*b = save;
}

void insertion_sort ( int list[], int left, int right )
{
int i, j;
	for ( i = left + 1; i < right; i++ ) {
		int save = list[i];
		for ( j = i; j > 0 && list[j - 1] > save; j-- )
			list[j] = list[j - 1];
	list[j] = save;
}
}


int median ( int list[], int left, int right )
{
/* Find the median of three values in list, use it as the pivot */
	int mid = ( left + right ) / 2;
	if ( list[left] > list[mid] )
	swap ( &list[left], &list[mid] );
	if ( list[left] > list[right] )
	swap ( &list[left], &list[right] );
	if ( list[mid] > list[right] )
	swap ( &list[mid], &list[right] );
	swap ( &list[mid], &list[right - 1] );
	
	return list[right - 1];
}

struct pivots partition ( int list[], int left, int right )
{
	int k;
	int i = left, j = right - 1;
	int m = left, n = right - 1;
	int pivot = median ( list, left, right );
	struct pivots ret;
/* Three way partition <,==,> */
	for ( ; ; ) {
	while ( list[++i] < pivot )
		while ( list[--j] > pivot ) {
		if ( j == left )
		break;
	}
	if ( i >= j )
	break;
	swap ( &list[i], &list[j] );
	if ( list[i] == pivot )
	swap ( &list[++m], &list[i] );
	if ( list[j] == pivot )
	swap ( &list[--n], &list[j] );
			}		
	swap ( &list[i], &list[right - 1] );
	j = i - 1;
	i = i + 1;
	for ( k = left; k < m; k++, j-- )
	swap ( &list[k], &list[j] );
	for ( k = right - 1; k > n; k--, i++ )
	swap ( &list[k], &list[i] );
	ret.left = i;
	ret.right = j;

	return ret;
}

void quicksort_r ( int list[], int left, int right )
{
	/* Terminate on small subfiles */
	if ( left + CUTOFF <= right ) {
	struct pivots pivot = partition ( list, left, right );
	quicksort_r ( list, left, pivot.right );
	quicksort_r ( list, pivot.left, right );
					}
}

void quicksort ( int list[], int n )
{
	int left = 0;
	int right = n-1;
	quicksort_r ( list, left, right - 1 );
	/* Insertion sort on almost sorted list */
	insertion_sort ( list, left, right );
}
