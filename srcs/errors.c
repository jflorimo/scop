#include <stdio.h>
#include "../includes/scop.h"

void exit_error_file(char *str)
{
	printf("File not found: %s (404 NOT FOUND)\n", str);
	exit (0);
}