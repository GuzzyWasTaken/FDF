/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:48:08 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/20 15:30:26 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	linelen(t_data	*data, char	*line)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	if (!line)
		exit (0);
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 1)
		{
			width++;
			while (line[i] && ft_isdigit(line[i]) == 1)
				i++;
		}
		i++;
	}
	if (width > data->width)
		data->width = width;
}

int	insert(char *line, t_data *data, int height)
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
	i = 0;
	while (data->map[height][i])
	{
		if (data->map[height][i] > 10000 || data->map[height][i] < -10000)
		{
			write(2, "Invalid map\n", 13);
			fdf_free(array);
			return (1);
		}
		i++;
	}
	fdf_free (array);
	return (0);
}

void	second_parse(t_data *data)
{
	int		height;
	int		width;
	char	*line;

	height = -1;
	width = 0;
	data->map = ft_calloc(data->height, sizeof(int *));
	if (!data->map)
		exit (0);
	while (++height < data->height)
	{
		data->map[height] = ft_calloc((data->width + 1), sizeof(int));
		if (!data->map[height])
		{
			exit (0);
		}
	}
	map_height(height, data);
}

void	check_map(char	*line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) == 1 || line[i] == ' ' || \
			line[i] == '-' || line[i] == '+' || line[i] == '\n'))
		{
			write(2, "Invalid map\n", 13);
			exit(0);
		}
		else
			i++;
	}
}

void	read_map(t_data	*data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(data->arg_map, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(0);
	while (line != NULL)
	{
		check_map(line, data);
		linelen(data, line);
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
	second_parse(data);
}
