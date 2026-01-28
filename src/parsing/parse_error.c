#include "minirt.h"

void parse_error(int code, char *s)
{
	//need to add cleanup
	printf("%s\n", s);
	exit(code);
}
