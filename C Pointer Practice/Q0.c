/* CS261- Assignment 1 - Q. 0*/
/* Name: Sarah Harber
 * Date: 1-15-17
 * Solution description: Program that declares an integer, prints the address of the variable. 
 * Then passes the address of the variable into a function which prints the value of the pointer,
 * the address of the value the pointer is pointing to, and hte address of hte pointer itself
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	  printf("Value of iptr: %d \n", *iptr);
     
	  /*Print the address pointed to by iptr*/
	  printf("Address pointed to by iptr: %p \n", iptr);

     /*Print the address of iptr itself*/
	  printf("Address of iptr itself: %p \n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 100;
    
    /*print the address of x*/
	printf("Address of x: %p \n", &x);

    /*Call fooA() with the address of x*/
	fooA(&x);

    /*print the value of x*/
	printf("Value of x: %d \n", x);
    
    return 0;
}
