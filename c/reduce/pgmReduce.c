#include "error.h"
#include "pgm_image.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
    if (argc != 4)
    {
        printf("ERROR: Bad Argument Count");

        return EXIT_WRONG_ARG_COUNT;
    }

    PGMImage property;

    int status = pgmb2a(&property, argv[1]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    int reduce_num = atoi(argv[2]);

    int original_height = property.height;

    property.height = property.height / reduce_num;
    property.width = property.width / reduce_num;
    property.maxValue = property.maxValue;

    status = pgma2b(&property, argv[3]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    for (int i = 0; i < original_height; i++)
    {
        free(property.data[i]);
    }

    free(property.data);

    return EXIT_NO_ERRORS;
}