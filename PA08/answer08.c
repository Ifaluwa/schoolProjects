#include<stdio.h>
#include<stdlib.h>


#include "answer08.h"

SparseNode * SparseNode_create(int index, int value)
{
	SparseNode *node = malloc(sizeof(SparseNode));
	node->index = index;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}
SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if(value == 0) return array;
  if(array == NULL)
 {
   return SparseNode_create(index, value);
 }
	if(array->index == index)
	{
	array->value = value;
	}
	else if(array->index > index)
	{
	array->left = SparseArray_insert(array->left, index, value);
	}
	else if(array->index < index)
	{
	array->right = SparseArray_insert(array->right, index, value);
	}
	
	return array;
}

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
	int i;
  SparseNode * array;
  array = NULL;
  for(i = 0; i < length; i++)
  {
    if (values[i] != 0)
    {
      array = SparseArray_insert(array, indices[i], values[i]);
    }
  }
  return array;
}

void SparseArray_destroy(SparseNode * array)
{

	if(array == NULL) return;
	SparseArray_destroy(array->left);	
	SparseArray_destroy(array->right);
	free(array);
}
	
int SparseArray_getMin(SparseNode * array)
{
	if(array == NULL) return;
  while(array -> left != NULL)
  {
    array = array->left;
  }
  return array-> index;
}

int SparseArray_getMax(SparseNode * array)
{
	if(array == NULL) return;
 while(array -> right != NULL)
  {
    array = array->right;
  }
  return array-> index;
}

SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
	if(array == NULL) return NULL;
	if(array->index == index) return array;
	if(array-> index > index)
	{
		 return SparseArray_getNode(array->left, index);
	}
	else
	{
		return  SparseArray_getNode(array->right, index);
	}
}

SparseNode * SparseArray_remove(SparseNode * array, int index)
{
	if (array == NULL)
  {
    return NULL;
  }
  if (index < (array -> index))
  {
    array -> left = SparseArray_remove(array -> left, index);
    return array;
  }
  if (index > (array -> index))
  {
    array -> right = SparseArray_remove(array -> right, index);
    return array ;
  }
  if (((array -> left) == NULL) && (array -> right) == NULL)
  {
    free (array);
    return NULL;
  }
  if ((array -> left) == NULL)
  {
    SparseNode * array1 = array -> right;
    free(array);
    return array1;
  }
  if ((array -> right) == NULL)
  {
    SparseNode * array2 = array -> left;
    free(array);
    return array2; 
  }
  SparseNode * array3 = array -> right; 
  while ((array3 -> left) != NULL)
  {
    array3 = array3 -> left;
  }

  array -> index = array3 -> index; 
  array -> value = array3 -> value;
  array3 -> index = index;
  array -> right = SparseArray_remove(array -> right, index);
  return array;
}

SparseNode * SparseArray_copy(SparseNode * array)
{
  if (array == NULL)
  {
    return NULL;
  }
  SparseNode * array1 = SparseNode_create(array -> index, array -> value); 
  array1 -> left = SparseArray_copy(array -> left);
  array1 -> right = SparseArray_copy(array -> right);
  
  return array1;
}

SparseNode * SparseArray_mergeinsert(SparseNode * array, int index, int value )
{
  if(value == 0)
  {
    return array;
  }
  
  if (array == NULL)
  {
    return SparseNode_create(index, value);
  }
  if (index == (array -> index))
  {
    array -> value += value;
    if((array -> value) == 0)
    {
      array = SparseArray_remove(array, array -> index);
    }
    return array;
  }
  if (index < (array -> index))
  {
    array -> left = SparseArray_mergeinsert(array -> left, index, value);
  }
  if (index > (array -> index))
  {
    array -> right = SparseArray_mergeinsert(array -> right, index, value);
  }
  return array;
}

SparseNode * merge_assist(SparseNode * array1copy, SparseNode * array_2)
{ 
  if(array_2 == NULL)
  {
    return(array1copy);
  }
  
  array1copy = merge_assist(array1copy, array_2 -> left);
  array1copy = merge_assist(array1copy, array_2 -> right);
  array1copy = SparseArray_mergeinsert(array1copy, array_2 -> index, array_2 -> value);
  
  return (array1copy);
}

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
	SparseNode * array1copy = SparseArray_copy(array_1);
  	array1copy = merge_assist(array1copy, array_2);
  	return (array1copy);
}


