#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "answer09.h"

HuffNode * HuffNode_create(int value)
{
        HuffNode *node = malloc(sizeof(HuffNode));
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
        Stack->head = NULL;
        free(stack);
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
}

int Stack_isEmpty(Stack * stack)
{
        return stack->head = NULL;
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
