#ifndef PGM_IMAGE_H
#define PGM_IMAGE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.h"

typedef struct PGMImage {
    char pgmType[3];
    unsigned char** data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} PGMImage;

int pgmb2a(PGMImage *, const char *);
int pgma2b(PGMImage *, const char *);

#endif