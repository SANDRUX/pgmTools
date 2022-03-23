#include "pgm_image.h"

void ignoreComments(FILE* fp)
{
    int ch;
    char line[100];
 
    // Ignore any blank lines
    while ((ch = fgetc(fp)) != EOF && isspace(ch));
 
    // Recursively ignore comments
    // in a PGM image commented lines
    // start with a '#'
    if (ch == '#') 
    {
        fgets(line, sizeof(line), fp);
        ignoreComments(fp);
    }
    else
    {
        fseek(fp, -1, SEEK_CUR);
    }
}

int pgmb2a(PGMImage* pgm, const char* filename)
{
    // Open the image file in the
    // 'read binary' mode
    FILE* pgmfile = fopen(filename, "rb");
 
    // If file does not exist,
    // then return
    if (pgmfile == NULL) {
        printf("ERROR: Bad File Name %s\n", filename);
        return EXIT_BAD_FILENAME;
    }
 
    ignoreComments(pgmfile);
    fscanf(pgmfile, "%s", pgm->pgmType);
 
    // Check for correct PGM Binary
    // file type
    if (pgm->pgmType[0] != 'P') {
        printf("ERROR: Bad Magic Number %s", filename);
        return EXIT_BAD_MAGIC_NUMBER;
    }
 
    ignoreComments(pgmfile);
 
    // Read the image dimensions
    fscanf(pgmfile, "%d %d", &(pgm->width), &(pgm->height));
 
    ignoreComments(pgmfile);
 
    // Read maximum gray value
    fscanf(pgmfile, "%d", &(pgm->maxValue));
    ignoreComments(pgmfile);
 
    // Allocating memory to store
    // img info in defined struct
    pgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char*));
 
    // Storing the pixel info in
    // the struct
    //in case of binary file
    if (pgm->pgmType[1] == '5') 
    {
        fgetc(pgmfile);
 
        for (int i = 0; i < pgm->height; i++) 
        {
            pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
 
            // If memory allocation
            // is failed
            if (pgm->data[i] == NULL) {
                printf("ERROR: Image Malloc Failed");
                return EXIT_MALLOC_FAIL;
            }
 
            // Read the gray values and
            // write on allocated memory
            fread(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
        }
    }

    //in case of ascii file
    else
    {
        fgetc(pgmfile);

        for (int i = 0; i < pgm->height; i++)
        {
            //allocate memory on the heap for image data
            pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
        }

        //create temporary buffer to store image data
        unsigned char imageData[pgm->width * pgm->height];


        //read data from the pgm file
        for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + pgm->width * pgm->height; nextGrayValue++)
        {
            int grayValue = -1;
            int scanCount = fscanf(pgmfile, "%u", &grayValue);

            if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
            { 
                
                for (int i = 0; i < pgm->height; i++)
                {
                    free(pgm->data[i]);
                }
            
                free(pgm->data);

                fclose(pgmfile);

                printf("ERROR: Bad Max Gray Value %s\n", filename);	
            
                return EXIT_BAD_MAX_GRAY_VALUE;
            } 

            *nextGrayValue = (unsigned char) grayValue;
        }

        //copy value from temporary buffer to the original one
        for (int i = 0; i < pgm->height; i++)
        {
            memcpy(pgm->data[i], imageData, pgm->width * sizeof(unsigned char));
        }

    }

    //close file and return the code
    fclose(pgmfile);
 
    return EXIT_NO_ERRORS;
}