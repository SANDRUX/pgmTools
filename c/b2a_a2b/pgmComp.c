#include "pgm_image.h"

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        printf("ERROR: Bad Argument Count");

        return EXIT_WRONG_ARG_COUNT;
    }

    PGMImage image_in, image_out;

    int status = pgmb2a(&image_in, argv[1]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    status = pgmb2a(&image_out, argv[2]);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    if ((image_in.height * image_in.width) != (image_out.height * image_out.width))
    {
        printf("DIFFERENT");
    }

    for (int i = 0; i < image_in.height; i++)
    {
        for (int j = 0; j < image_in.width; j++)
        {
            if (image_in.data[i][j] != image_out.data[i][j])
            {
                printf("DIFFERENT");

                return EXIT_NO_ERRORS;
            }
        }
    }

    printf("IDENTICAL");

    return EXIT_NO_ERRORS;
}