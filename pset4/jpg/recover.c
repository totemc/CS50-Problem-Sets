/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

// define block size as 512 const
#define BLOCK 512



int main(int argc, char* argv[])
{
    // create lost file to search for signatures
    FILE* lost = fopen("card.raw","r");
    
    // array to check blocks
    uint8_t size[BLOCK];
    
    // counter for file names
    int counter = 0;
    
    // read lost file
    fread(size,BLOCK,1,lost);
    
    // check to see if a file pic is open
    bool isopen = false;
    
    // create pic pointer to write to 
    FILE* pic;
    
   
    
    // while not end of file, for each block
    while (fread(size,BLOCK,1,lost) == 1)
    {
        
        // check for sig, if sig found
        if ((size[0] == 0xff && size[1] == 0xd8 && size[2] == 0xff && size[3] == 0xe0) || (size[0] == 0xff && size[1] == 0xd8 && size[2] == 0xff && size[3] == 0xe1))
        {
            // char of name to store sprintf into, credits to 
            char name[8];
            
            // sprintf (credits to http://www.reddit.com/r/cs50/comments/2kp4so/pset5_recover_question_about_sprintf_and_about/) counter into name
            sprintf(name, "%03d.jpg", counter);
            
            // if file is not open
            if (isopen == false)
            {
                // open file 0xx.jpg
                pic = fopen(name,"w");
                // write to it
                fwrite(size,BLOCK,1,pic);
                // isopen set to true
                isopen = true;
                // in order to not skip over 002, must use if if, not if if else to rewrite 000 and then counter++
                
            }
            // if file is open
            if(isopen == true)
            {
                // close previous opened file
                fclose(pic);
                // open new file
                pic = fopen(name,"w");
                // write to it
                fwrite(size,BLOCK,1,pic);
                // increment counter
                counter++;
            }      
        }
        // else, if no signature is found
        else
        {
            // if a file is open
            if(isopen == true)
            {
                // write junk values to be overwritten
                fwrite(size,BLOCK,1,pic);
            }
        }    
         
    }
    // close opened files
    fclose(lost);
    fclose(pic);
    
    // the end
    return 0;
}
