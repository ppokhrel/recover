

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // data to store blocks
    unsigned char buffer[512];

    // output file
    FILE *img = NULL;

    // counter for jpegs
    int count = 0;

    //variable to flag when a jpeg is found
    int inJPEG = 0;

    while ((fread(&buffer, 512, 1, inptr)) == 1)
    {

        // check first three bytes of the block
        if (buffer[0] == 0xFF && buffer[1] == 0xd8 && buffer[2] == 0xFF)
        {

            // create an output filename
            char filename[10];
            sprintf(filename, "%03d.jpg", count);

            //create new file
            img = fopen(filename, "w");

            //write buffer data to file
            fwrite(&buffer, 512, 1, img);

            //remember that we found a jpeg
            inJPEG = 1;

            // increment number of jpeg found
            count++;
        }
        else
        {

            //if this block is part of a jpeg then write it, if not ignore the block
            if (inJPEG == 1)
            {
                fwrite(&buffer, 512, 1, img);
            }
        }

    }

}
