/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    /*if (n<1)
    {
        return false;
    }
    
    
    for (int i = 0; i < n ; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
        
    }
    return false;
    */
    bool found = false;
    int index = 0;
    int last = n;
    int middle;
    
    while (!found && index <= last)
    {
        middle = (index + last)/2;
        if (values[middle] == value)
        {
            found = true;
            return true;
        }
        else if (values[middle] > value)
        {
            last = middle-1;
        }
        else
        {
            index = middle + 1;
        }
    }
    return false;
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < (n-1) ; i++)
    {
        int min = i;
        for (int j = (i+1); j < n ; j++)
        {
            if (values[j] < values[min])
            {
                min = j;
            }
            
        }
        if (min != i)
        {
            int tmp = values[i];
            values[i] = values[min];
            values[min] = tmp;
            //hello
        }
    }
    
    return;
}
