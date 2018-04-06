/* CS261- Assignment 1 - Q.3*/
/* Name: Sarah Harber
 * Date: January 22, 2017
 * Solution description: Create an array of 20 items, print the array, then sort the array, then re-print the array.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

/*******************************************************************
* * Description: Function to sort an array of elements from smallest
* * to largest.
*******************************************************************/
void sort(int* number, int n) {
	/*Sort the given array number , of length n*/
	int i; // Variable for loop
	int a; // Variable for loop
	int smallest; //Variable to hold the smalleset number
	int temporary=NULL; 
	for (i = 0; i < n-1; i++) //Loop through each element 
	{
		smallest = i; //Set smallest to first element
		for (a = i + 1; a < n; a++)
		{
			if (number[a] < number[smallest]) //If element inspected less than the smallest element
				smallest = a; //Make smaller element the smallest
		}
		if (smallest != i) //If the first element is not the smallest
		{
			temporary = number[i]; //Placehold for element in i
			number[i] = number[smallest]; // Swap the smallest element into the lower element
			number[smallest] = temporary; // Place the temporary element into the other element.

		}
	}

}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *numbers = malloc(n * sizeof(numbers));

    /*Fill this array with random numbers, using rand().*/
	int a;
	for (a = 0; a < n; a++)
	{
		numbers[a] = rand() %1000 + 1;
	}

    /*Print the contents of the array.*/
	for (a = 0; a < n; a++)
	{
		printf("%d\n", numbers[a]);
	}
    /*Pass this array along with n to the sort() function of part a.*/
	sort(numbers, n);

    /*Print the contents of the array.*/    
	for (a = 0; a < n; a++)
	{
		printf("%d\n", numbers[a]);
	}

    return 0;
}
