#include "minirt.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	b;

	i = 0;
	b = ft_strlen(s);
	while (i <= b)
	{
		if ((unsigned char)c == s[i])
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int ft_strlen(const char *s)
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

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	i = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	sub = malloc((len + 1) * sizeof(*s));
	if (sub == NULL)
		return (NULL);
	while (len > 0)
	{
		sub[i] = s[start + i];
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
