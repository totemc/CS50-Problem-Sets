// credits to copy.c and cs50 for the skeleton
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    
    while (n<0 || n>100)
    {
        printf("Please enter a number greater than or less than 100\n");
        return 1;  
        
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // orignal padding values before resize
    int padding2 =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // temporary variables that hold new values for resized image (outptr)
    //int filesize = bf.bfSize;
    long width = bi.biWidth;
    long height = bi.biHeight;
    int imagesize = bi.biSizeImage;
    
    // temporary variables to hold orignal values of inptr
    // int og_filesize = bf.bfSize;
    long og_width = bi.biWidth;
    long og_height = bi.biHeight;
    // int og_imagesize = bi.biSizeImage;
    
    // multiply height and width by n
    width = (width)*n;
    height = (height)*n;
    
    
    // store new height and width into headerfile variables
    bi.biWidth = width;
    bi.biHeight = height;
    
    // determine padding for scanlines after image resize
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    
    
    // imagesize is width*sizeof(pixels)+padding*absolute value of height since its negative(bottom top)
    imagesize = (bi.biWidth*sizeof(RGBTRIPLE)+padding)*abs(bi.biHeight);
    // put this value into bi.biSizeImage (size of image)
    bi.biSizeImage = imagesize;
    // size of file is image size + 54 (offset)
    bf.bfSize = bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    

    // for original height times
    for (int i = 0, biHeight = abs(og_height); i < biHeight; i++)
    {   
        // for n times
        for (int j = 0; j < n ; j++)
        {
            // go over scanlines
            for (int k = 0; k < og_width ; k++)
            {
                // create temp storage
                RGBTRIPLE triple;
                // read it and store it in triple
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // copy each pixel n times
                for (int l = 0; l < n ; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add new padding if any
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }
            
            // go to beg of scanline
            if (j < (n-1))
            {
                fseek(inptr, -og_width*sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding from infile
        fseek(inptr,padding2, SEEK_CUR);
       
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
