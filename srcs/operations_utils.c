#include "../includes/scop.h"

char *trim(char *str)
{
	char *end;

	// Trim leading space
	while(ft_isspace(*str)) str++;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + ft_strlen(str) - 1;
	while(end > str && ft_isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}
