#include "pgm_image.h"

int pgma2b(PGMImage * pgm, const char * filename)
{
    FILE * file = fopen(filename, "wb");


    if (file == NULL)
    {
        printf("ERROR: Bad File Name %s\n", filename);
        return EXIT_BAD_FILENAME;
    }

    // Writing Magic Number to the File
    fprintf(file, "P2\n");

    // Writing Width and Height
    fprintf(file, "%d %d\n", pgm->width, pgm->height);

    // Writing the maximum gray value
    fprintf(file, "255\n");

    for (int i = 0; i < pgm->height; i++)
    {
        for (int j = 0; j < pgm->width; j++)
        {
            fprintf(file, "%d ", pgm->data[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    return EXIT_NO_ERRORS;
}