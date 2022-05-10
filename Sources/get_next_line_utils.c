/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 16:11:04 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/04/14 17:24:46 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_strchr(const char *src, int c)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (src[i] == (char)c)
			return (i + 1);
		i++;
	}
	if (src[i] == (char)c)
		return (i + 1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	if (*s1 == '\0' && *s2 == '\0')
	{
		free (s1);
		return (ft_strdup(""));
	}
	str = ft_calloc((ft_strlen(s1) + (ft_strlen(s2) + 1)), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (*s2)
	{
		str[i] = *s2++;
		i++;
	}
	free (s1);
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*p;
	int		i;

	i = 0;
	p = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!p)
		return (NULL);
	while (s[i] != 0)
	{
		p[i] = s[i];
		i++;
	}
	return (p);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char				*p;
	unsigned int		i;
	unsigned int		count;

	count = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup("\0"));
	if (len > i || start > i)
		len = i;
	p = ft_calloc((len + 1), sizeof(char));
	if (!p)
		return (NULL);
	while (len > 0)
	{
		p[count] = s[start];
		count++;
		start++;
		len--;
	}
	return (p);
}
