/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 16:10:21 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/05/18 15:57:43 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*ft_read(int fd, char *stat_str)
{
	int		read_ret;
	char	*read_str;

	read_ret = 1;
	read_str = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	while (ft_strchr(stat_str, '\n') == 0 && read_ret != 0)
	{
		read_ret = read(fd, read_str, BUFFER_SIZE);
		read_str[read_ret] = '\0';
		if (read_ret == -1)
			return (0);
		else if (!stat_str)
			stat_str = ft_strdup(read_str);
		else
			stat_str = ft_strjoin(stat_str, read_str);
	}
	return (stat_str);
}

char	*clean_str(char *stat_str)
{
	int			nl_pos;
	char		*str;

	nl_pos = ft_strchr(stat_str, '\n');
	if (!nl_pos)
		return (stat_str);
	str = ft_substr(stat_str, 0, nl_pos);
	return (str);
}

char	*get_end(char *read_str)
{
	int		nl_pos;
	char	*str;

	nl_pos = ft_strchr(read_str, '\n');
	if (!nl_pos)
		return (ft_strdup(""));
	str = ft_substr(read_str, nl_pos, ft_strlen(read_str) - nl_pos);
	free (read_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*temp_str;
	char			*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	if (!temp_str)
		temp_str = ft_calloc(1, sizeof(char));
	if (!temp_str)
		return (NULL);
	temp_str = ft_read(fd, temp_str);
	if (temp_str == NULL)
		return (NULL);
	if (!temp_str[0])
	{
		free (temp_str);
		temp_str = NULL;
		return (NULL);
	}
	ret_str = clean_str (temp_str);
	temp_str = get_end (temp_str);
	return (ret_str);
}

char	*ft_calloc(size_t count, size_t size)
{
	char		*ptr;
	size_t		i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < count)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
