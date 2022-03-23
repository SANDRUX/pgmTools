#include "pgm_utility.h"

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        printf("Usage is ./pgmComp file1.pgm file2.pgm");

        return EXIT_WRONG_ARG_COUNT;
    }

    struct pgm_property first, second;
    
    int status = read_pgm_data(argv[1], &first);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    status = read_pgm_data(argv[2], &second);

    if (status != EXIT_NO_ERRORS)
    {
        return status;
    }

    //check if file contents match
    if (first.size != second.size)
    {
        printf("DIFFERENT");
    }

    else 
    {
        status = 0;

        for (long i = 0; i < first.size; i++)
        {
            if (first.data[i] != second.data[i])
            {
                status = 1;
                break;
            }
        }
        //print the output
        if (status == 1)
        {
            printf("DIFFERENT");
        }

        else
        {
            printf("IDENTICAL");
        }
    }

    free(first.data);
    free(second.data);

    return EXIT_NO_ERRORS;
}

