//Include libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) //main function
{
    //prompt the user to enter their name
    //printf("Please enter your full name.\n");
    //user input assigned to string 'c' 
    string c = GetString(); 
    //create a variable to initials array size, initialized at 1 to account for the constant first name entered
    int d = 1; 
    
    //loop to iterate through the user input and convert all letters to uppercase
    for (int i = 0, n = strlen(c) ; i < n ; i++)
    {
        //printf("%c\n",toupper(c[i]));
        c[i] = toupper(c[i]);
        
    }
    
    //loop to increment d for each space found in user input
    for (int i = 0, n = strlen(c) ; i < n ; i++)
    {
        if (c[i] == ' ')
        {
            d += 1;
        }
    }
    
    //printf("%d\n", d);
    
    //create char array with size of 1+however many more spaces (AKA initials) are present
    char initials[d];
    //sets the first index of the initials array to the first char (initial) of the user input index
    initials[0] = c[0];
    
    //printf("%c\n", initials[0]);
    
    //loop that checks for every space in the user input and assigns the index of the space + 1 to an index of the char array
    for (int i = 0, b = 1, n = strlen(c) ; i < n ; i++)
    {
        if (c[i] == ' ')
        {
            initials[b] = c[i+1];
            b++;
        }
    }
    
    //finally prints out the initials stored in the char array
    for (int i = 0 ; i < d ; i++)
    {
        printf("%c",initials[i]);
    }
    
    //new line for sexy formatting
    printf("\n");
}
