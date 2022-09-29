#include <stdio.h>
#include "calculator_handlers.h"
#include "calculator_operators.h"
#include "stack.h"



/* ------  handlers domain ------- */
static void GetOperand(stack_ty *operands, double *arg);
static void ExecOp(hd_ty *th_, operator_ty *op);
static double DigitToVal(const char *digit);

/* must confirm to fsm typedef int (*fptr)(void *);  */

int OnOperator(void *th__)
{
	hd_ty *th_ = (hd_ty *)th__;
	
	/*  resolve which operator it is */
	operator_ty *curr_op = IsOperator(*th_->token);
	operator_ty *prev_op = StackPeek(th_->operators);

	/* no empty stack case, there is dummy in the bottom on init */
	
	/* while prev wins */
	while (IsStronger(prev_op, curr_op))/* positive if a has higher precedence, 0 if b */
	{
		/* call-remove prev */
		ExecOp(th_, prev_op);
		
		/* update prev  */
		prev_op = StackPeek(th_->operators);
	}
	
	/* always -  push operator to stack */
	StackPush(th_->operators, curr_op);
}


int OnDigit(void *th__)
{
	hd_ty *th_ = (hd_ty *)th__;
	
	double digit = DigitToVal(th_->token);
	
	
	/* push digit to stack */
/*
	printf("push digit %f \n", digit);
*/
	StackPush(th_->operands, *(void **)&digit);
}


int OnErr(void *th__)
{
	hd_ty *th_ = (hd_ty *)th__;
	
	/* log to std err */
	puts("on err\n");
	(void)th_;
}


static void GetOperand(stack_ty *operands, double *operand)
{
	void *operand_ptr = StackPeek(operands);
	
	/* pop stack */
	StackPop(operands);
	
	/* write to target */
	*operand =  *(double *)&operand_ptr;
}


static void ExecOp(hd_ty *th_, operator_ty *op)
{
	double arg1, arg2;
	double result;
	
	GetOperand(th_->operands, &arg2);
	GetOperand(th_->operands, &arg1);
		
	/* call prev func */
	
	result = ExecOperatorFunc(op,arg1, arg2);
			
	/* push the result on stack */
	StackPush(th_->operands, *(void **)&result); 
		
	/* remove used operator */
	StackPop(th_->operators);	
}


static double DigitToVal(const char *digit)
{
	return *digit - '0'; 
}

