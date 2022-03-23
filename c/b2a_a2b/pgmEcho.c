#include "pgm_image.h"

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        printf("ERROR: Bad Argument Count");

        return EXIT_WRONG_ARG_COUNT;
    }

    PGMImage image;

    int status = pgmb2a(&image, argv[1]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    status = pgma2b(&image, argv[2]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    printf("ECHOED");

    return EXIT_NO_ERRORS;
}