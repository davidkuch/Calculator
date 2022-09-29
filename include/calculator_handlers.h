
#include "stack.h"

typedef struct hd hd_ty;

struct hd
{
	stack_ty *operands;
	stack_ty *operators;
	const char *token;
};

int OnOperator(void *th_);
int OnDigit(void *th_);
int OnErr(void *th_);
