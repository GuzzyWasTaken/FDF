/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:48:08 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/13 17:27:45 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//FIX THIS 

void	linelen(t_data	*data, char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 || line[i] == '-' || line[i] == '+')
			while (line[i] != ' ' || line[i] != '\n' || line[i] != '\0')
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

void	check_map(char	*line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i]) == 1 || line[i] == ' ' || line[i] == '\n'))
		{
			write(2, "Invalid map\n", 13);
			exit(1);
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
	check_map(line, data);
	linelen(data, line);
	while (line != NULL)
	{
		check_map(line, data);
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
	second_parse(data);
}