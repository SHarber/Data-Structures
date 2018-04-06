/* CS261- Assignment 1 - Q.4*/
/* Name: Sarah Harber
 * Date: January 22, 2017
 * Solution description:  Program to sort an array of n students in ascending order by score.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/   
	 /*Sort the given array number , of length n*/
	int i; // Variable for loop
	int a; // Variable for loop
	int smallest; //Variable to hold the smalleset number
	int temporary = NULL;
	int temporaryid = NULL;
	for (i = 0; i < n - 1; i++) //Loop through each element 
	{
		smallest = i; //Set smallest to first element
		for (a = i + 1; a < n; a++)
		{
			if (students[a].score < students[smallest].score) //If element inspected less than the smallest element
				smallest = a; //Make smaller element the smallest
		}
		if (smallest != i) //If the first element is not the smallest
		{
			temporary = students[i].score; //Placehold for element in i
			temporaryid = students[i].id; //Placeholder for id element
			students[i].score = students[smallest].score; // Swap the smallest element into the lower element
			students[i].id = students[smallest].id;//Swap the smallest element into the lower element
			students[smallest].score = temporary; // Place the temporary element into the other element.
			students[smallest].id = temporaryid; //Place the temporary element into the other element

		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 10;
    
    /*Allocate memory for n students using malloc.*/
	struct student *students = malloc(n * sizeof(struct student));

    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	int i; //Variable for loop
	int a; //Variable for loop

	int id;
	int score;

	for (i = 0; i < 10; i++) // Loop to assign ids and scores to students.
	{
		id = rand() % 10 + 1;

		//Determine if id has been used by any other students
		for (a = 0; a < (i + 1); a++) //Cycles through the students whose id are already assigned
		{
			while (students[a].id == id)//if the id is the same as another student
			{
				id = rand() % 10 + 1; // Generate a new id. 
				a = 0; //Make sure the new id hasn't been use by going to the beginning of the loop
			}
		}

		score = rand() % 100 + 1; //Generate a random number between 1 and 100 for the student's score.
		students[i].id = id; //Assign randomly genereated id to the student
		students[i].score = score;  //Assign randomly generated score to the student
	}

    /*Print the contents of the array of n students.*/
		for (a = 0; a < 10; a++)
	{
		printf("%d %d\n", students[a].id, students[a].score);
	}

    /*Pass this array along with n to the sort() function*/
		sort(students, n);

    /*Print the contents of the array of n students.*/
		for (a = 0; a < 10; a++)
		{
			printf("%d %d\n", students[a].id, students[a].score);
		}

    return 0;
}
