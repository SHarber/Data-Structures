#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
	struct data* leftnum = (struct data*) left; //Variable to store dereferenced left.
	struct data* rightnum = (struct data*) right; //Variable to store dereferenced right.

	//Compare the numbers
	if (leftnum->number < rightnum->number) //If left number is less than right number
		return -1; //Return -1
	else if (leftnum->number > rightnum->number) //If left number is greater than right number
		return 1; //Return 1
	else
		return 0; //Otherwise return 0.

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
	struct data * num = (struct data*) curval; //Create a new variable to hold hte dereferenced curval.
	printf("%d ", num->number); //Print the number.

}


