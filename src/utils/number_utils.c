#include <minirt.h>

double	parse_number(const char *str)
{
	int	i;
	int	sign;
	double  div;
	double	integer;
	double  decimal;

	integer = 0.0;
	decimal = 0.0;
	div = 1;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		parse_error(EXIT_FAILURE, "Invalid number");
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = integer * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		if (str[i] < '0' || str[i] > '9')
			parse_error(EXIT_FAILURE, "Invalid number");
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal = decimal * 10 + str[i] - '0';
			div = div * 10;
			i++;
		}
	}
	while (ft_isspace(str[i])) //skip the /n
		i++;
	if (str[i] != '\0')
		parse_error(EXIT_FAILURE, "Invalid characters after number");
	decimal = decimal / div;
	return ((float)sign * (integer + decimal));
}
