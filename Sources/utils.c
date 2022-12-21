/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 11:14:39 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/20 16:04:33 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	map_height(int height, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(data->arg_map, O_RDONLY);
	line = get_next_line(fd);
	if (insert(line, data, i) == 1)
	{
		free(line);
		close(fd);
		exit(0);
	}
	free(line);
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (insert(line, data, i) == 1)
		{
			free(line);
			close(fd);
			exit(0);
		}
		free(line);
	}
}

void	fdf_free(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

float	maximum(float y, float x)
{
	if (y > x)
		return (y);
	return (x);
}

void	isometric(float *x, float *y, int z, t_data *data)
{
	*x = (*x - *y) * cos(data->angle);
	*y = (*x + *y) * sin(data->angle) - (z * 3);
}
