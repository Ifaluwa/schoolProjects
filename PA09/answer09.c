#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "answer09.h"
#include "treefun.h"

HuffNode * HuffNode_create(int value)
{
        HuffNode *node = malloc(sizeof(HuffNode));
        node->value = value; 
	node->left = NULL;
        node->right = NULL;
        return node;
}

void HuffNode_destroy(HuffNode * tree)
{
        if(tree == NULL) return;
        HuffNode_destroy(tree->left);
        HuffNode_destroy(tree->right);
        free(tree);
}

Stack * Stack_create()
{
        Stack * stack = malloc(sizeof(Stack));
        stack->head = NULL;
        return stack;
}

void Stack_destroy(Stack * stack)
{
        if (stack == NULL) return;
        StackNode * node = stack->head;
        while(node != NULL)
        {
        StackNode *tmp = node;
        node = node->next;
        HuffNode_destroy(tmp->tree);
        free(tmp);
        }
	free(stack);
}

int Stack_isEmpty(Stack * stack)
{
        return stack->head == NULL;
}

HuffNode * Stack_popFront(Stack * stack)
{
        if(Stack_isEmpty(stack)) return NULL;
        HuffNode *tree = stack->head->tree;
        StackNode *tmp = stack->head;
        stack->head = tmp->next;
        free(tmp);
        return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	if(stack == NULL) return;
	StackNode *node = malloc(sizeof(StackNode));
	node->tree = tree;
	node->next = stack->head;
	stack->head = node;
}

void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode *first = Stack_popFront(stack);
	HuffNode *second = Stack_popFront(stack);
	HuffNode *new_node = HuffNode_create(0);
	new_node->right = first;
	new_node->left = second;
	Stack_pushFront(stack, new_node);
}

size_t Stack_size(Stack *stack)
{
	if(stack == NULL) return 0;
	size_t count = 0;
	StackNode *node = stack->head;
	while (node != NULL)
	{
	count++;
	node = node->next;
	}
	return count;		
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	Stack *stack = Stack_create();
	int val;
	while((val = fgetc(fp)) != EOF)
	{
		if(val == '1')
		{
		val = fgetc(fp);
		Stack_pushFront(stack, HuffNode_create(val));
		}
		else if(val == '0')
		{
		if(Stack_size(stack) == 1) break;
		Stack_popPopCombinePush(stack);
		}
	}
	HuffNode *tree = Stack_popFront(stack);
	Stack_destroy(stack);
	return tree;
}

typedef struct{
	FILE *fp;
	unsigned char byte;
	int position;
}BitFile;

BitFile *BitFile_create(FILE *fp)
{
	BitFile *bitfile = malloc(sizeof(BitFile));
	bitfile->fp = fp;
	bitfile->byte = 0;
	bitfile->position = 8;
	return bitfile;
}

void BitFile_destroy(BitFile *bitfile)
{
	free(bitfile);
}

int BitFile_nextBit(BitFile *bitfile)
{
	if(bitfile->position == 8)
	{
	bitfile->position = 0;
	if(fread(&(bitfile->byte), sizeof(unsigned char), 1, bitfile->fp) != 1)
	{
	return -1;
	}
	}

	int val = (bitfile->byte >> (7 - bitfile->position)) & 1;
	bitfile->position++;
	return val;
}

int BitFile_nextByte(BitFile *bf)
{
	int ret = 0;
	int pos;
	for(pos = 0; pos < 8; pos++)
	{
	int bit = BitFile_nextBit(bf);
	if (bit < 0) return -1;
	ret = ret | (bit << (7 - pos));
	}
	return ret;
	
}
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	Stack *stack = Stack_create();
	BitFile *bf = BitFile_create(fp);
	int val = BitFile_nextBit(bf);
	while(val >= 0)
	{
	if (val == 1)
	{
		val = BitFile_nextByte(bf);
	Stack_pushFront(stack, HuffNode_create(val));
	}
	else if(val == 0)
	{
	if(Stack_size(stack) == 1) break;
	Stack_popPopCombinePush(stack);
	}
	val = BitFile_nextBit(bf);
	}
	
	HuffNode *tree = Stack_popFront(stack);	
	Stack_destroy(stack);	
	BitFile_destroy(bf);	
	return tree;
}









