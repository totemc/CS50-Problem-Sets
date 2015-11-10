#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    
    
    //if the 2nd space which is default 'NULL' is not 'NULL' (aka too many arguments entered), then the program returns 1 and an error message.
    if (argv[1] == NULL)
    {
        printf("You entered no arguments.\n");
        return 1;
    }
    else if (argv[2] != NULL)
    {
        printf("You entered too many arguments.\n");
        return 1;
    }
    
    //creates the amount we will be shifting by converting command line input to integer
    int key = atoi(argv[1]);
    
    
    //printf("key is : %i\n",key);
    
    
    //printf("Enter some plaintext to encrypt.\n");
    //user input of to be encrypted text stored into 'code'
    string code = GetString();
    
    //printf("Your plaintext is: %s\n", code);
    
    //string crypt[strlen(code)];
    
    
    
    //printf("%i\n",strlen(code));
    
    //constant variable l for the loops
    int l = strlen(code);
    
    //loop that goes through the string array and changes the letters according to the key
    for(int i = 0; i < l ; i++)
    {
        if (isspace(code[i]) || isdigit(code[i]))
        {
            code[i] = code[i];
        }
        else if (isupper(code[i]))
        {
            int tmp = code[i];
            tmp = tmp - 'A';
            tmp = tmp + key;
            tmp = tmp%26;
            tmp = tmp + 'A';
            code[i] = tmp;
        }
        else if (islower(code[i]))
        {
            int tmp2 = code[i];
            tmp2 = tmp2 - 'a';
            tmp2 = tmp2 + key;
            tmp2 = tmp2%26;
            tmp2 = tmp2 + 'a';
            code[i] = tmp2;
        }
    }
    
    printf("%s\n", code);
    return 0;
    
    //printf("\n");
    
    
    
    
    
    
    
    
}
