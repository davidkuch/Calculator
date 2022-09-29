

enum {RTL= 0, LTR = 1};

typedef struct operator operator_ty;
typedef double (*op_func_ty)(double , double);

struct operator
{
	char symbol;
	int precedence;
	int associativity;
	op_func_ty op_func;
};


const operator_ty *IsOperator(char symbol);

/* positive if a has higher precedence, 0 if equal, negative if b is higher */
int IsStronger(operator_ty *a,operator_ty *b);

double ExecOperatorFunc(operator_ty *a, double arg1, double arg2);


/* for debug */
void PrintOp(operator_ty *a);
