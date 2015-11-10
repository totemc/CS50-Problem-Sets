#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    bool ok = false;
    
    printf("O hai! How much change is owed?\n"); //ask user for change input
    
    float floatChange = GetFloat(); //user inputs change
    
    //loop that continues to ask user for change if input is negative. ends the program if input is 0
    while (!ok)
    {
        if (floatChange < 0)
        {
            printf("O hai! How much change is owed?\n");
            floatChange = GetFloat();
        }
        else if (floatChange == 0)
        {
            return 0;
        }
        else
        { 
            ok = true;
        }
    }
    
    floatChange = floatChange * 100; //converts dollars to cents
    
    int intChange = round(floatChange); //rounds
    
    bool zero = false; //boolean to end upcoming loop
    int coin = 0; //initialize counter
    
    //printf("%f\n",intChange);
    //printf("%d\n",intChange);
    
    
    //subtracts money amount and ups the coin counter until change left == 0
    do
    {
        if (intChange >= 25)
        {
            intChange = intChange-25;
            coin = coin + 1;
        }
        else if (intChange >= 10)
        {
            intChange = intChange-10;
            coin = coin + 1;
        }
        else if (intChange >= 5)
        {
            intChange = intChange-5;
            coin = coin + 1;
        }
        else if (intChange >= 1)
        {
            intChange = intChange-1;
            coin = coin + 1;
        }
        else if (intChange == 0)
        {
            zero = true;
        } 
    }while(!zero);
    
    printf("%d\n",coin); //prints amount of coins 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
