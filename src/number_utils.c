/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:14:30 by jinzhang          #+#    #+#             */
/*   Updated: 2026/03/04 10:22:13 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitypes.h"
#include "parsing.h"
#include <stdlib.h>

static void	determine_sign(const char *str, int *i, int *sign)
{
	*sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -(*sign);
		(*i)++;
	}
}

static int	parse_ending(const char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] != '\0')
		return (1);
	return (0);
}

static int	add_decimal(const char *str, int *i, double *decimal, double *div)
{
	*decimal = 0.0;
	*div = 1.0;
	if (str[*i] == '.')
	{
		(*i)++;
		if (str[*i] < '0' || str[*i] > '9')
			return (1);
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			*decimal = (*decimal) * 10 + str[*i] - '0';
			*div = (*div) * 10;
			(*i)++;
		}
	}
	return (0);
}

static int	add_integer(const char *str, int *i, double *integer)
{
	*integer = 0.0;
	if (str[*i] < '0' || str[*i] > '9')
		return (1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*integer = (*integer) * 10 + str[*i] - '0';
		(*i)++;
	}
	return (0);
}

int	parse_number(const char *str, t_f64 *out)
{
	int		i;
	int		sign;
	t_f64	div;
	t_f64	integer;
	t_f64	decimal;

	i = 0;
	if (!str || !out)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	determine_sign(str, &i, &sign);
	if (add_integer(str, &i, &integer))
		return (1);
	if (add_decimal(str, &i, &decimal, &div))
		return (1);
	if (parse_ending(str, &i))
		return (1);
	decimal = decimal / div;
	*out = (float)sign * (integer + decimal);
	return (0);
}
