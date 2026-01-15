#include "minirt.h"

int ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while(s[i])
	{
		i++;
	}
	return  (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
