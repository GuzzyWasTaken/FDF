/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:48:08 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/12 16:58:55 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	linelen(t_data	*data, char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		printf("hello\n");
		if (((line[i] >= '0') && (line[i] <= '9')) || line[i] == '-' || line[i] == '+')
			while (line[i] != ' ')
				i++;
		data->width++;
		i++;
	}
}

void	insert(char *line, t_data *data, int height)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(line, ' ');
	while (array[i])
	{
		data->map[height][i] = ft_atoi(array[i]);
		i++;
	}
	free (array);
}

void	second_parse(t_data *data)
{
	int		height;
	int		width;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	height = -1;
	width = 0;
	data->map = ft_calloc(data->height, sizeof(int *));
	if (!data->map)
		exit (0);
	while (++height < data->height)
	{
		data->map[height] = ft_calloc((data->width + 1), sizeof(int));
		if (!data->map[height])
			exit (0);
	}
	fd = open(data->arg_map, O_RDONLY);
	line = get_next_line(fd);
	insert(line, data, i);
	i++;
	while (i < data->height)
	{
		line = get_next_line(fd);
		insert(line, data, i);
		free(line);
		i++;
	}
}

int	check_map(char	*line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalnum(line[i]) == 1 || line[i] == ' ' || line[i] == '\n' \
		|| line[i] == '-' || line[i] == '+')
		{
			if (line[i] == ' ' && line[i + 1] == ' ')
				return (1);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

void	read_map(t_data	*data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(data->arg_map, O_RDONLY);
	line = get_next_line(fd);
	linelen(data, line);
	while (line != NULL)
	{
		if (check_map(line, data) == 1)
		{
			perror("Invalid map");
			exit(1);
		}
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
	second_parse(data);
}