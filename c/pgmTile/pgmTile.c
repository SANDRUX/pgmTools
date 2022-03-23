#include "error.h"
#include "pgm_image.h"
#include <stdio.h>

char* replaceWord(const char * s, const char * oldW, const char * newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) 
    {
        if (strstr(&s[i], oldW) == &s[i]) 
        {
            cnt++;
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
    return result;
}

int main(int argc, char ** argv)
{
    // Print error if arguments are not placed correctly
    if (argc != 4)
    {
        printf("ERROR: Bad Argument Count");

        return EXIT_WRONG_ARG_COUNT;
    }

    // Read data from the main image
    PGMImage property;

    int status = pgmb2a(&property, argv[1]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    // Set properties

    int dimension = atoi(argv[2]);

    int size = (property.height * property.width) / (dimension * dimension);

    PGMImage content[size];

    // Allocate 2 dimensional array on the heap

    for (int i = 0; i < size; i++)
    {
        content[i].data = (unsigned char **)malloc(dimension * sizeof(unsigned char *));

        for (int j = 0; j < dimension; j++)
        {
            content[i].data[j] = (unsigned char *)malloc(dimension * sizeof(unsigned char));
        }
    }

    // Copy image matrix to small matrices
    for (int p = 0; p < property.height; p += dimension)
    {
        for (int q = 0; q < property.width; q += dimension)
        {
            int i = p / dimension * property.width / dimension + q / dimension;

            for (int m = 0; m < dimension; m++)
            {
                for (int n = 0; n < dimension; n++)
                {
                    content[i].data[m][n] = property.data[p + m][q + n];                    
                }
            }            
        }
    }
    
    // Generate file names and place chunk datas inside them
    for (int i = 0; i < size; i++)
    {   
        char row[20];
        sprintf(row, "%d", (i * dimension) / property.width);
        char * filename = replaceWord(argv[3], "<row>", row);
        char column[20];
        sprintf(column, "%d", i % (property.width / dimension));
        char * final_filename = replaceWord(filename, "<column>", column);
        content[i].height = dimension;
        content[i].width = dimension;
        content[i].maxValue = property.maxValue;
        
        pgma2b(&content[i], final_filename);

        free((void *)filename);
        free((void *)final_filename);
    }

    // Freeing or Deallocating heap memory because it is not needed anymore
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            free(content[i].data[j]);
        }

        free(content[i].data);
    }

    printf("TILED");

    return EXIT_NO_ERRORS;
}