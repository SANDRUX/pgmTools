#include <stdio.h>
#include <stdlib.h>
#include "utilitiesPgm.h"

int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */
	
	struct pgm_property property;

	int status = read_pgm_data(argv[1], &property);

	if (status != EXIT_NO_ERRORS)
	{
		return status;
	}

	status = write_pgm_data(argv[2], &property);

	if (status != EXIT_NO_ERRORS)
	{
		return 0;
	}

	free(property.data);

	printf("ECHOED");

	return EXIT_NO_ERRORS;
} 
