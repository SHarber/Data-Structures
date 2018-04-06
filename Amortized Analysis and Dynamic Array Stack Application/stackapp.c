/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:returns 1 if the string is ballanced.
*/
int isBalanced(char* s)
{

	struct DynArr * holdArray = newDynArr(20); //Create a new array.
	char chartocmp;//Variable to hold the char to be compared.
	chartocmp = nextChar(s);//Pull in next char
	while (chartocmp != 0)//While the next char is not a 0
	{
		if (chartocmp == '{' || chartocmp == '(' || chartocmp == '[') //If char is an opening Brace, bracket, or parenthesis
			pushDynArr(holdArray, chartocmp); //Push it onto a stack

		if (chartocmp = '}') //If it is a end brace
			if (topDynArr(holdArray) == '{') //Check to see if the top of hte stack is a front brace
				popDynArr(holdArray); //then pop the value
		if (chartocmp = ']') //If it is a end brace
			if (topDynArr(holdArray) == '[') //Check to see if the top of hte stack is a front brace
				popDynArr(holdArray); //then pop the value
		if (chartocmp = ')') //If it is a end brace
			if (topDynArr(holdArray) == '(') //Check to see if the top of hte stack is a front brace
				popDynArr(holdArray); //then pop the value
		chartocmp = nextChar(s);
	}

	if (sizeDynArr(holdArray) != 0)//If there is values left in the array
		return 0;
	else
		deleteDynArr(holdArray);//delete the array
		return 1;



	return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}
