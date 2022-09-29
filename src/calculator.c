#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "calculator_handlers.h"
#include "calculator_operators.h"
#include "fsm.h"
#include "stack.h"

#define STACK_SIZE 100

typedef struct calculator
{
	fsm_ty *fsm;
	hd_ty hd;
}calculator_ty;

typedef enum events{DIGIT, OPERATOR ,EQUAL ,NUM_EVENTS}events_ty;
typedef enum states {WAIT_DIGIT, WAIT_OP , GOT_EQUAL , ERR , NUM_STATES}states_ty;

double bark(double a, double b);
static calculator_ty *CreateCalculator(const char *exp);
static states_ty RunCalculator(calculator_ty *th_, const char *exp, double *result);	
static void Destroy(calculator_ty *th_);
static events_ty TokenToEvent(const char *token);
static int IsDigit(const char *token);




double Calculate(const char *exp)
{
	double ret = NAN;
	int state = ERR;
	calculator_ty *calculator = NULL;
	
	assert(exp != NULL);
	
	/* create-init calculator() */
	calculator = CreateCalculator(exp);

	if (calculator == NULL)
	{
		puts("malloc create err!\n");
		abort();
	}
		
	/* run the calculator() */
	state = RunCalculator(calculator, exp, &ret);
	
	/* resolve the result of the calculation */
	if (state == ERR)
	{
		ret = NAN;
	}	

	/*  destroy */
	Destroy(calculator);
	
	/*  return ret */
	return ret;
}


static calculator_ty *CreateCalculator(const char *exp)
{
	/* create state and func matrix and init it */
	static const state_ty mat[NUM_STATES][NUM_EVENTS]= 
	{
	/* state\ event   digit            operator                  equal     */
	/* wait digit */{{WAIT_OP,OnDigit},{ERR,OnErr}              ,{ERR,OnErr}},
	/* wait op   */	{{ERR,OnErr}      ,{WAIT_DIGIT,OnOperator}  ,{EQUAL,OnOperator}},
	/* equal     */	{{ERR,OnErr}    ,{ERR,OnErr}                ,{ERR,OnErr}},
	/* err       */	{{ERR,OnErr}     ,{ERR,OnErr}               ,{ERR,OnErr}}
	};
									                    
	static const operator_ty dummy = {'@', -120, LTR, bark}; 								                    								  
	/* malloc struct for calculator */
	calculator_ty *th_ = (calculator_ty *)malloc(sizeof(calculator_ty));

	if (th_ == NULL)
	{
		return NULL;
	}
	
	/* create fsm() - pass the matrix */
	fsm_ty *fsm = FSMCreate(NUM_STATES, NUM_EVENTS,(const state_ty *) mat);
	
	if (fsm == NULL)
	{
		free(th_);
		return NULL;
	}
	
	/* create 2 stacks, operands and operators */
	stack_ty *operands = StackCreate(STACK_SIZE);

	/*  check null */
	if (operands == NULL)
	{
		free(th_);
		free(fsm);
		return NULL;
	}
	
	stack_ty *operators = StackCreate(STACK_SIZE);
	/*  check null */
	if (operators == NULL)
	{
		free(th_);
		free(fsm);
		free(operands);
		return NULL;
	}


	/* assign creations to calculator */
	th_->fsm = fsm;
	th_->hd.operands = operands;
	th_->hd.operators = operators;
	th_->hd.token = exp; 
	
	/* push to operators stack dummy op to avoid empty stack special case */
	StackPush(th_->hd.operators, &dummy);
	
	/* return calculator */
	return th_;
}


static states_ty RunCalculator(calculator_ty *th_, const char *exp, double *result)
{
	/* start with state Start */
	states_ty state = WAIT_DIGIT;
	events_ty event;
	void *result_ptr;
	
	assert(th_ != NULL);
	assert(exp != NULL);
	assert(result != NULL);
	
	
	/* for each char in exp: */
	while (*th_->hd.token != '\0')
	{
		/* event = char_to_event(char) */
		event = TokenToEvent(th_->hd.token);
			
		/* current state = call fsm-get-next-state(curr state, event, *hd) */
		state = FSMTransit(th_->fsm,  state,  event, &(th_->hd));
		
		++(th_->hd.token);
	}
	
	/* get the result */
	result_ptr = StackPeek(th_->hd.operands);
	*result = *(double *)&result_ptr;
	
	return state;
}
	
	
static void Destroy(calculator_ty *th_)
{
	/* call destroy fsm */
	FSMDestroy(th_->fsm);
	
	/* free all allocs and th_ */
	StackDestroy(th_->hd.operands);
	StackDestroy(th_->hd.operators);
	
	free(th_);
}


static events_ty TokenToEvent(const char *token)
{
	events_ty event;

	if (IsDigit(token))
	{
		event = DIGIT;
	}

	if (*token == '=') /* equal is special case of operator */
	{
		event = EQUAL;
	}
	
	else if (IsOperator(*token)) 
	{
		event = OPERATOR;
	}
	
	return event;
}


static int IsDigit(const char *token)
{
	return ((*token >= '0') && (*token <= '9'));
}


double bark(double a, double b)
{
	puts("bark bark!!\n");
}
