#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    bool ok = false;
    //ask user for half-pyramid height
    printf("Please enter a height for the half-pyramid: \n");
    int height = GetInt();
    
    //if height is greater than 23, or a negative number, it repeats the prompt to the user
    while (!ok)
    {
        if (height > 23)
        {
            printf("I'm sorry, your input integer was too high! Please enter a height for the half-pyramid: \n");
            height = GetInt();
        }
        else if (height < 0)
        {
            printf("I'm sorry, your input was a negative integer! Please enter a positive number for the half-pyramid: \n");
            height = GetInt();
        }
        else if (height == 0)
        {
            return 0;
        }
        else
        { 
            ok = true;
        }
    }
    
    //loop that creates the half-pyramid
    
    for (int i = 0; i < height; i++) //loops through the loops to create as many lines as the height the user input and creates a new line after each hash and space are printed
    {
        for(int j = 0; j < ((height-i)-1); j++) //prints as many spaces according to what line & height of the input
        {
            printf(" ");
        }
        for(int k = 0; k < (i+2); k++) //prints as many hashes, starting at 2 depending on what line the loop is on
        {
            printf("#");
        }
        printf("\n");
    }
    
    
    
    
    
    
    
    
    

        

        

    
}
