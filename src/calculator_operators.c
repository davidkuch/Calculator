#include <stdlib.h>
#include "calculator_operators.h"


static double Add_Func(double a, double b);
static double Subtract_Func(double a, double b);
static double Multiply_Func(double a, double b);
static double Devide_Func(double a, double b);

#define NUM_OPS 5

const operator_ty *IsOperator(char symbol)
{
	static const operator_ty operators[NUM_OPS] =
	{
		{'+', 1, LTR ,Add_Func },
		{'-', 1, LTR ,Subtract_Func },
		{'*', 2, LTR,Multiply_Func },
		{'/', 2, LTR, Devide_Func},
		{'=', -1,LTR ,NULL }
	};
	
	int i = 0;
	const operator_ty *ret = NULL;
	
	/* compare symbol to each symbol in operators structs array */
	for (;i < NUM_OPS; ++i)
	{
		if (operators[i].symbol == symbol)
		{
			ret = operators + i;
		}
	}
	
	/* return pointer to operator found, or null if not found */	
	return ret;
}


/* positive if a has higher precedence, 0 if b */
int IsStronger(operator_ty *a,operator_ty *b)
{
	if (a->precedence > b->precedence)
	{
		
		return 1;
	}
	
	if (a->precedence == b->precedence && a->associativity == LTR)
	{
		return 1;
	}
	

	return 0;
}


double ExecOperatorFunc(operator_ty *a, double arg1, double arg2)
{
	if  (a->op_func == NULL)
	{
		puts("null indirection. abort!\n");
		abort();
	}
/*
	puts("exec ");
	PrintOp(a);
	printf("%f %f \n", arg1, arg2);
*/
	return a->op_func(arg1, arg2);
}

/* for debug */
void PrintOp(operator_ty *a)
{
	printf("op %c ", a->symbol);
}

/* ---- op funcs ----- */


static double Add_Func(double a, double b)
{
	return a + b;
}


static double Subtract_Func(double a, double b)
{
	return a - b;
}


static double Multiply_Func(double a, double b)
{
	return a * b;
}


static double Devide_Func(double a, double b)
{
	return a / b;
}

