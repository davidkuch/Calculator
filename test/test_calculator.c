#include "test_runner.h"
#include "calculator.h"

const char exp1[] = "1+1="; 
const char exp3[] = "1+1+2="; 
const char exp4[] = "1+1-2="; 
const char exp5[] = "1*2-3="; 
const char exp6[] = "3*4/2-3+5="; 
const char exp7[] = "3*3*3-2*5="; 
const char exp8[] = "2-9*3+8/2="; 
#define NUM_EQUATIONS 7

const char *equations[] = {exp1 ,exp3 ,exp4 ,exp5 ,exp6 ,exp7 ,exp8};

int test1()
{
 	int err = 0;
 	
 	
 	printf("calculate(%s) = %f \n", exp1, Calculate(exp1));
 
 	return err;
}

int test2()
{
 	int err = 0;
 	
 	printf("calculate(%s) = %f \n", exp1, Calculate(exp1));
  	printf("calculate(%s) = %f \n", exp3, Calculate(exp3));	
  	printf("calculate(%s) = %f \n", exp4, Calculate(exp4));	
 	printf("calculate(%s) = %f \n", exp5, Calculate(exp5));	
 	
 	return err;
}

int test3()
{
 	int err = 0;
 	
 	int i = 0;
 	
 	for(; i < NUM_EQUATIONS;++i)
 	{
 		printf("%s %f \n",equations[i], Calculate(equations[i]));
 	}
 
 	return err;
}

int test4()
{
 	int err = 0;
  		printf("%s %f \n",equations[4], Calculate(equations[4]));
 	return err;
}

int test5()
{
 	int err = 0;
 
 	return err;
}

int test6()
{
 	int err = 0;
 
 	return err;
}

int test7()
{
 	int err = 0;
 
 	return err;
}

int test8()
{
 	int err = 0;
 
 	return err;
}

int test9()
{
 	int err = 0;
 
 	return err;
}

int test10()
{
 	int err = 0;
 
 	return err;
}

int test11()
{
 	int err = 0;
 
 	return err;
}

int test12()
{
 	int err = 0;
 
 	return err;
}

int test13()
{
 	int err = 0;
 
 	return err;
}

int test14()
{
 	int err = 0;
 
 	return err;
}

int test15()
{
 	int err = 0;
 
 	return err;
}
