#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct stack stack_ty;

/* returns NULL if malloc failed, O(1) */
stack_ty *StackCreate(size_t capacity);

/* undefined for empty stack, O(1) */
void StackPop(stack_ty *stack);

/* undefined for empty stack, O(1) */
void *StackPeek(stack_ty *stack);

/* undefined if size is full, O(1) */
void StackPush(stack_ty *stack, void *val);

/* boolean if stack is empty, O(1)  */
int StackIsEmpty(stack_ty *stack);

/* get the stack maximum size , O(1)*/
size_t Capacity(stack_ty *stack);

/* get the stack current size, number of existing elements, O(1) */
size_t Size(stack_ty *stack);

/* free memory, O(1)  */
void StackDestroy(stack_ty *stack);


#endif
