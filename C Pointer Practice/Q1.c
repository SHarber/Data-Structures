/* CS261- Assignment 1 - Q.1*/
/* Name: Sarah Harber
 * Date: January 17, 2107
 * Solution description:  Program to create an array of 10 students, assign random unique ids, and random unique scores.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

/**********************************************************************
* * Description: Function to allocate memory for 10 new students
**********************************************************************/
struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *newstudents =	malloc(10 * sizeof(struct student)); 

     /*return the pointer*/
	return newstudents;
}

/***********************************************************************
* * Description: Function to assign a unique ID to the students and
* * to assign a randomly generated score to the students.
***********************************************************************/
void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     
	int i; //Variable for loop
	int a; //Variable for loop

	int id;
	int score;

	for (i = 0; i < 10; i++) // Loop to assign ids and scores to students.
	{
		id = rand() % 10 + 1;

		//Determine if id has been used by any other students
		for (a = 0; a < (i+1); a++) //Cycles through the students whose id are already assigned
		{
			while (students[a].id == id)//if the id is the same as another student
			{
				id = rand() % 10 + 1; // Generate a new id. 
				a = 0; //Make sure the new id hasn't been use by going to the beginning of the loop
			}
		}
		
		score = rand() % 100 + 1 ; //Generate a random number between 1 and 100 for the student's score.
		students[i].id = id; //Assign randomly genereated id to the student
		students[i].score = score;  //Assign randomly generated score to the student
	}
}

/***********************************************************************
* * Description: Function to output the scores and ids of the students
***********************************************************************/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int a; //Variable for loop
	
	for (a = 0; a < 10; a++)
	{
		printf("%d %d\n", students[a].id, students[a].score);
	}

}

/**********************************************************************
* * Description: Function to get the minimum, maximum and average of 
* * the student's scores and print to the user.
**********************************************************************/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     //Create a loop to find the minimum, maximum and average scores
	
	int i;//Variable for loop
	int min = 101;
	int max = 1;
	int average = 0;

	for (i = 0; i < 10; i++) // Create a loop through each student
	{
		if (students[i].score <= min) //If that student's score is smaller it is the new min
			min = students[i].score;
		if (students[i].score >= max) //If that students score is higher it is the new max
			max = students[i].score;
		average = average + students[i].score; //Add students score to the total sum.
	}
	average = average / 10; //Divide by 10 to get the average.
	printf("Minimum: %d\n", min);
	printf("Maximum: %d\n", max);
	printf("Average: %d\n", average);

}

/**********************************************************************
* * Description: Function to Deallocate the memory allocated in an 
* * array.
**********************************************************************/
void deallocate(struct student* stud) {
	/*Deallocate memory from stud*/
	if (stud != NULL)
		free(stud);
}	

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();

    /*call generate*/
	generate(stud);

    /*call output*/
	output(stud);

    /*call summary*/
	summary(stud);

    /*call deallocate*/
	deallocate(stud);

    return 0;
}
