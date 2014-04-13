#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "tree.h"
#include "answer10.h"

Stack * Stack_create()
{
 	Stack * stack = malloc(sizeof(Stack));
        stack->list = NULL;
        return stack;	
}

void Stack_destroy(Stack * stack)
{
 	if (stack == NULL) return;
        ListNode * head = stack->list;
        while(head != NULL)
        { 
        ListNode *tmp = head;
        head = head->next;
        free(tmp);
        }
        free(stack);
}

int Stack_isEmpty(Stack * stack)
{
	return (stack == NULL) || (stack->list == NULL);
}

int Stack_popFront(Stack * stack)
{
	int val = stack->list->value;
	ListNode *tmp = stack->list;
	stack->list = stack->list->next;
	free(tmp);
	return val;
}

void Stack_pushFront(Stack * stack, int value)
{
	ListNode *node = malloc(sizeof(ListNode));
	node->value = value;
	node->next = stack->list;
	stack->list = node;
}

int Stack_peek(Stack * stack)
{
	return stack->list->value;
}

void stackSort(int * array, int len)
{
	int write_index = 0;
	Stack *stack = Stack_create();
	int ind;
	for(ind = 0; ind < len; ind++)
	{
	int x = array[ind];
		while(!Stack_isEmpty(stack) && x > Stack_peek(stack))
		{
		int value = Stack_popFront(stack);	
		array[write_index++] = value;
		}
		Stack_pushFront(stack, x);
	}
	while(!Stack_isEmpty(stack))
	{
	array[write_index++] = Stack_popFront(stack);
	}
	Stack_destroy(stack);
}


#define TRUE 1
#define FALSE 0
int max_index(int *array, int len)
{
	int ind;
	int max = array[0];
	int max_ind = 0;
	for(ind = 0; ind < len; ind++)
	{
		if(array[ind] > max)
		{
		max = array[ind];
		max_ind = ind;
		}
	}
	return max_ind;
}

int min_index(int *array, int len)
{
	int ind;
	int min = array[0];
	int min_ind = 0;
	for(ind = 0; ind < len; ind++)
	{
		if(array[ind] < min)
		{
		min = array[ind];
		min_ind = ind;
		}
	}
	return min_ind;
}
	
int isStackSortable(int * array, int len)
{
	if(len < 3) return TRUE;
	int max_ind = max_index(array, len);
	int *left_array = array;
	int left_len = max_ind;
	int *right_array = array + max_ind + 1;
	int right_len = len - (max_ind + 1);
	
	if(left_len > 0 && right_len > 0)
	{
	int max_left_ind = max_index(left_array, left_len);
	int min_right_ind = min_index(right_array, right_len);
	if(left_array[max_left_ind] > right_array[min_right_ind])
	{
	return FALSE;
	}
	}
	
	if(!isStackSortable(left_array, left_len)) return FALSE;
	if(!isStackSortable(right_array, right_len)) return FALSE;
	return TRUE;

}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void permute(int *array, int pos, int len)
{
	if(pos == len)
	{
	if(isStackSortable(array, len))
	{
		TreeNode *tree = Tree_build(array,len);
		Tree_printShape(tree);
		Tree_destroy(tree);
	}
	}

	else
	{
	int ind;
	for(ind = pos; ind < len; ind++)
		{
		swap(&(array[ind]), &(array[pos]));
		permute(array, pos + 1, len);
		swap(&(array[pos]), &(array[ind]));
		}
	}

}


void genShapes(int n)
{
 	int *array = malloc(sizeof(int) * n);
	int ind;
	for(ind = 0; ind < n; ind++)
	{
	array[ind] = ind;
	}
	permute(array, 0, n);
	free(array);	
}
