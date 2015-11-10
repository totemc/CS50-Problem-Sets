#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //if no arguments entered, return 1
    if (argv[1] == NULL)
    {
        printf("You entered no arguments.\n");
        return 1;
    }
    //if more than 1 argument entered, return 1
    else if (argv[2] != NULL)
    {
        printf("You entered too many arguments.\n");
        return 1;
    }
    
    //check the characters of the argument entered for a digit, return 1 if one is found.
    for(int i = 0; i < 1 ; i++)
    {
        for(int j = 0, m = strlen(argv[1]) ; j < m ; j++)
        {
            if (isdigit(argv[1][j]))
            {
                printf("You included a digit. Please try again.\n");
                return 1;
            }
        }
        
    }
      
    //printf("%s\n", argv[1]);
    
    //initialize keyword variable that holds the key to the encryption
    int size = 0; 
    
    //increment keyword for each character in the argument
    for (int j = 0, m = strlen(argv[1]) ; j < m ; j++)
    {
        size += 1;
    }
    
    
    
    //create a string that is identical to argument/user input
    string keyword = argv[1];
    
    //create a char array that is the same size of the length of the string (to avoid having to [][] loop to print or ascess single characters
    char code[size];
    
    //assign each char in keyword to temporary char and assign that to the index of the code array while making them all lowercase
    for ( int i = 0; i < size ; i++ )
    {
        char tmp = tolower(keyword[i]);
        code[i] = tmp;
    }
    
    
    //create phrase string that gets user input to encrypt
    string phrase = GetString();
    
    //creates variable that holds length of phrase
    int l = strlen(phrase);
    
    
    //loop through the arrays and encrypt
    for (int i = 0, n=0; i < l ; i++,n++)
    {
        if (!isalpha(phrase[i]))
        {
            phrase[i] = phrase [i];
            n -= 1;
            
        }
        else if (isupper(phrase[i]))
        {
            int tmp = phrase[i];
            
            
            int key = code[n%size] - 'a';
            
            //int tmp2 = code[i%size];
            
            tmp = tmp - 'A';
            tmp = tmp + key;
            tmp = tmp%26;
            tmp = tmp + 'A';
            
            phrase[i] = tmp;
        }
        else if (islower(phrase[i]))
        {
            int tmp = phrase[i];
            
            
            int key = code[n%size] - 'a';
            
            //int tmp4 = code[i%size];
            
            tmp = tmp - 'a';
            tmp = tmp + key;
            tmp = tmp%26;
            tmp = tmp + 'a';
            
            phrase[i] = tmp;
        }
        
        
    }
    
    //FINALLY print the freaking encrypted string
    printf("%s\n",phrase);
    return 0;
    
    
    
    
    
    
    
    
}
