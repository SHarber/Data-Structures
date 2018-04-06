/* CS261- Assignment 1 - Q.2*/
/* Name: Sarah Harber
 * Date: January 17, 2017
 * Solution description: Program to set 3 integers, pass them into a function and print the new values.
 */
 
#include <stdio.h>
#include <stdlib.h>
/********************************************************
* * Description: Double one value, half one value
* * Add those two values and store in another value
********************************************************/
int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = 2 * (*a);
	
    /*Set b to half its original value*/
	*b = (*b) / 2;

    /*Assign a+b to c*/
	c = (*a) + (*b);
	
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;

    /*Print the values of x, y and z*/
	printf("x = %i\n", x);
	printf("y = %i\n", y);
	printf("z = %i\n", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	int result = foo(&x, &y, z);

	/*Print the value returned by foo*/
	printf("Result: %d\n", result);

    /*Print the values of x, y and z again*/
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("z: %d\n", z);

    /*Is the return value different than the value of z?  Why?*/
	// The return value of z is not different as z was not passed by reference or as a pointer.
	// The function does not change teh value of z, only c.
    return 0;
}
    
    
