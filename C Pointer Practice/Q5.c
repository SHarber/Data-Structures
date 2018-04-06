/* CS261- Assignment 1 - Q.5*/
/* Name: Sarah Harber
 * Date: January 22, 2017
 * Solution description: Program to get a word from the user and convert to sticky caps.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}
/*******************************************************************
* * Description: Function to convert a word to sticky caps
*******************************************************************/
void sticky(char* word){
     /*Convert to sticky caps*/
	int i=0;
	
	while (word[i] != 0)
		{
			if ((i + 2) % 2 == 0)//Check to see if its an even number
			{
				//Check to see if the character is uppercase
				if (word[i] > 'Z')
					word[i] = toUpperCase(word[i]);
			}
			if ((i + 2) % 2 == 1)//Check to see if its an even number
			{
				//Check to see if the character is uppercase
				if (word[i + 2] <= 'Z')
					word[i + 2] = toLowerCase(word[i]);
			}
			i++;
		}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char word[20];
	scanf("%s", word);
	
    /*Call sticky*/
	sticky(word);

    /*Print the new word*/
	printf("%s\n", word);

    return 0;
}
