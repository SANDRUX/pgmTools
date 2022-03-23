#include "pgm_utility.h"

int read_pgm_data(char * filename, struct pgm_property * property)
{	
	//intialize variables
	unsigned char magic_number[2] = {'0','0'};
	unsigned short *magic_Number = (unsigned short *) magic_number;
	

	//initialize properties
	char *commentLine = NULL;

	unsigned int width = 0, height = 0;

	unsigned int maxGray = 255;

	unsigned char *imageData = NULL;
	
	//open file
	FILE *inputFile = fopen(filename, "r");

	if (inputFile == NULL)
    {
		printf("ERROR: Bad File Name %s", filename);
        return EXIT_BAD_FILENAME;
    }

	//read magic numbers aka format of pgm file
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);


	//throw error if magic number is incorrect
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
	{
		fclose(inputFile);

		printf("ERROR: Bad Magic Number %s\n", filename);
		
		return EXIT_BAD_MAGIC_NUMBER;
	}

	int scanCount = fscanf(inputFile, " ");

	// read comment line

	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
	{
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		if (commentString == NULL)
		{
			free(commentLine);	
			fclose(inputFile);

			printf("ERROR: Bad Comment Line %s\n", filename);	
					
			return EXIT_BAD_COMMENT_LINE;
		}
	}
	else
	{
		ungetc(nextChar, inputFile);
	}


	//read width, height and maxgray pixels
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));


	//check if dimensions dont exceed the ranges
	if 	(
		(scanCount != 3				)	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	) 	||
		(maxGray	!= 255		)
		)
	{
		free(commentLine);
	
		fclose(inputFile);
		
		printf("ERROR: Bad Dimensions %s\n", filename);	
		
		return EXIT_BAD_DIMENSIONS;
	}

	//allocate memory for image data
	long nImageBytes = width * height * sizeof(unsigned char);
	imageData = (unsigned char *) malloc(nImageBytes);

	if (imageData == NULL)
	{ 
		free(commentLine);

		fclose(inputFile);

		printf("ERROR: Image Malloc Failed %s\n", filename);	
		
		return EXIT_MALLOC_FAIL;
	}


	//read data (bit map) from the image
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
	{
		int grayValue = -1;
		int scanCount = fscanf(inputFile, "%u", &grayValue);

		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ 
			free(commentLine);
			free(imageData);	
		
			fclose(inputFile);

			printf("ERROR: Bad Max Gray Value %s\n", filename);	
		
			return EXIT_BAD_MAX_GRAY_VALUE;
		} 

		*nextGrayValue = (unsigned char) grayValue;
	} 


	//allocate memory for property data buffer
    property->data = (unsigned char *)malloc(nImageBytes);
    property->size = nImageBytes;

	//copy values from one buffer to another
    for (long i = 0; i < nImageBytes; i++)
    {
        property->data[i] = imageData[i];
    }

	fclose(inputFile);
	free(commentLine);
	free(imageData);

    return EXIT_NO_ERRORS;
}