#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
	int sum = 0;
	int i;
	for(i = 0; i < len; i++)
{
	sum += array[i];
}
    return sum;
}

int arrayCountNegative(int * array, int len)
{
	int i;
	int ct = 0;
	for(i = 0; i < len; i++)
{
	if(array[i] < 0)
{
	ct++;
}
}
    
	return ct;
}

int arrayIsIncreasing(int * array, int len)
{
	int i;
	int solution = 0;

	for(i = 1; i < len; i++)
{
	if(array[i] >= array[i-1])
{
	solution = 1;	
}
else
{
	solution = 0;
	break;
}
}
if (len == 0 || len == 1)
{
solution = 1;
}
	return solution;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
	int i;
	int solution = 0;
	for(i = len - 1; i >= 0; i--)
{
	if(haystack[i] == needle)
{
	solution = i;
	break;
}	
else
{
	solution = -1;
}
}
if (len == 0)
{
solution = -1;
}

	return solution;
}

int arrayFindSmallest(int * array, int len)
{
	int i;
	int solution = 0;
	int smallest = array[0];
	for(i = 1; i < len; i++)
{
	if(array[i] < smallest)
{
	smallest = array[i];
	solution = i;
}
}
if (len == 0)
{
	solution = 0;
}
	return solution;	
}



