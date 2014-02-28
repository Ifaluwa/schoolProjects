#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "answer06.h"
#define FALSE 0 
#define TRUE 1

void printPartition(int *partition, int length)
{
	int i;
	printf("= ");
	for(i = 0; i < length; i++)
	{
	if(i != 0) printf(" + ");
	printf("%d", partition[i]);	
	}
	printf("\n");
}

void partitionAllHelper(int N, int *partition, int pos)
{
	//BASE CASE	
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}

	//INDUCTIVE CASE	
	int i;
	for(i = 1; i <= N; i++)
	{
	partition[pos] = i;
	partitionAllHelper(N - i, partition, pos + 1);
	}

}

void partitionAll(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionAllHelper(value, partition, 0);
	free (partition);
}
void partitionIncreasingHelper(int N, int * partition, int pos)
{
	//BASE CASE
	if(N == 0)
	{printPartition(partition, pos);
	return;
	}

	//INDUCTIVE CASE
	int i;
	int start = pos == 0 ? 1 : partition[pos - 1] + 1;
	for(i = start; i <= N; i++)
	{
	partition[pos] = i;
	partitionIncreasingHelper(N - i, partition, pos + 1);
	}
		
}

void partitionIncreasing(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionIncreasingHelper(value, partition, 0);
	free (partition);
}

void partitionDecreasingHelper(int N, int * partition, int pos)
{
	//BASE CASE
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}

	//INDUCTIVE CASE
	int i;
	int start = pos == 0 ? N : partition[pos - 1] - 1;
	for(i = start; i > 0; i--)
	{
	partition[pos] = i;
	partitionDecreasingHelper(N - i, partition, pos + 1);
	}
}

void partitionDecreasing(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionDecreasingHelper(value, partition, 0);
	free(partition);
}

void partitionOddHelper(int N, int *partition, int pos)
{
	//BASE CASE
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}
	//INDUCTIVE CASE
	int i; 
	for(i = 1; i <= N; i+= 2)
	{
	partition[pos] = i;
	partitionOddHelper(N - i, partition, pos + 1);
	}
}
void partitionOdd(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionOddHelper(value, partition, 0);
	free(partition);
}
void partitionEvenHelper(int N, int * partition, int pos)
{
	//BASE CASE	
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}
	//INDUCTIVE CASE
	int i;
	for(i = 2; i <= N; i+= 2)
	{
	partition[pos] = i;
	partitionEvenHelper(N - i, partition, pos + 1);
	}
}
	

void partitionEven(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionEvenHelper(value, partition, 0);
	free(partition);
}
void partitionOddandEvenHelper(int N, int * partition, int pos)
{
	//BASE CASE
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}
	//INDUCTIVE CASE
	int i;
	for(i = 1; i <= N; i++)	
{
	int val = 0;
	if(pos == 0)
	{
	val = 1;
	}
	else
	{
	val = (partition[pos - 1] % 2) != (i % 2);
	}
	if(val == 1)
	{
	partition[pos] = i;
	partitionOddandEvenHelper(N - i, partition, pos + 1);
	}
}
}

void partitionOddAndEven(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionOddandEvenHelper(value, partition, 0);
	free(partition);
}
int isPrime(int number)
{
	int i;
	for(i = 2; i < number; i++)
	{
	if ((number % i) == 0) return FALSE;
	}
	return TRUE;
}

void partitionPrimeHelper(int N, int *partition, int pos)
{
	//BASE CASE
	if(N == 0)
	{
	printPartition(partition, pos);
	return;
	}
	//INDUCTIVE CASE
	int i;
	for(i = 2; i <= N; i++)
	{
	if(!isPrime(i)) continue;
	partition[pos] = i;
	partitionPrimeHelper(N - i, partition, pos + 1);
	}
}
void partitionPrime(int value)
{
	int *partition = malloc(sizeof(int) * value);
	partitionPrimeHelper(value, partition, 0);
	free(partition);
}





