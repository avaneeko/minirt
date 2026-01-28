#include "minirt.h"

void parse_error(int code, char *s)
{
	printf("%s\n", s);
	exit(code);
}
