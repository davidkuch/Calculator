#include <assert.h>
#include <stdlib.h>
#include "stack.h"

struct stack
{
	void **top;
	void **m_data;
	void **end;
};


/* returns NULL if malloc failed, O(1) */
stack_ty *StackCreate(size_t const capacity)
{
	size_t size = sizeof(stack_ty) + (sizeof(void **) * capacity);
	stack_ty *new = (stack_ty *)malloc(size);
	
	if (new != NULL)
	{
		new->m_data = (void **)(new + 1);
		new->top = new->m_data;
		new->end = new->m_data + capacity;
	}
	
	return new;
}

/* undefined for empty stack, O(1) */
void StackPop(stack_ty *stack)
{
	assert(stack != NULL);
	
	--stack->top;
}

/* undefined for empty stack, O(1) */
void *StackPeek(stack_ty *stack)
{
	assert(stack != NULL);
		
	return *(stack->top - 1);
}

/* undefined if size is full, O(1) */
void StackPush(stack_ty *stack, void *val)
{
	assert(stack != NULL);
	*stack->top = val;
	++stack->top;

}

/* boolean if stack is empty, O(1)  */
int StackIsEmpty(stack_ty *stack)
{
	assert(stack != NULL);
	
	/* if is empty */
	if (stack->top == stack->m_data)
	{
    	return 1;
    }
    
    /* if not empty */
	return 0;
}

/* get the stack maximum size , O(1)*/
size_t Capacity(stack_ty *stack)
{
	assert(stack != NULL);
	
	return (stack->end - stack->m_data);
}

/* get the stack current size, number of existing elements, O(1) */
size_t Size(stack_ty *stack)
{
	assert(stack != NULL);
	
	return (stack->top - stack->m_data);
}

/* free memory, O(1)  */
void StackDestroy(stack_ty *stack)
{
	assert(stack != NULL);
	
	free(stack);
	stack = NULL;
}

