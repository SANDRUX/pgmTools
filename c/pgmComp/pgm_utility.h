#ifndef PGM_UTILS_H
#define PGM_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILENAME 2
#define EXIT_BAD_MAGIC_NUMBER 3
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_MAX_GRAY_VALUE 6
#define EXIT_MALLOC_FAIL 7
#define EXIT_BAD_DATA 8
#define EXIT_ERROR_OUTPUT_FAIL 9
#define EXIT_BAD_LAYOUT 10
#define EXIT_MISCELLANEOUS 100

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

struct pgm_property
{
    unsigned char * data;
    long size;
};

int read_pgm_data(char *, struct pgm_property *);

#endif