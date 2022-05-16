#include <stdio.h>
#include "../includes/fdf.h"

// void	parse_info(t_data	*data)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	while(data->)

// }

//lines have to be the same length
// only numbers	
// void	second_parse(t_data	*data, int	fd)
// {
// 	int		height;
// 	int		width;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	height = 0;
// 	width = 0;
// 	while(data->map[height] <= data->height)
// 	{
// 		data->map[height] = malloc((width + 1) * sizeof(int));
// 		height++;
// 	}
// 	line = get_next_line(fd);
// 	insert(line, data->map[i]);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		insert(line, data->map[i]);
// 		free(line);
// 		i++;
// 	}
// }

// void insert(char	*line, int)
// {
// 	int	i;

// 	i = 0;
// 	while(line[i] != '\0')
// 	{
// 		map[i] = atoi(line[i]);
// 		i++;
// 	}
// }

int	check_map(char	*line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isalnum(line[i]) == 1 || line[i] == ' ' || line[i] == '\n')
		{
			if (line[i] == ' ' && line[i + 1] == ' ')
				return(1);
			i++;
		}
		else 
			return(1);
	}
	return (0);
}

void	linelen(t_data	*data, char	*line)
{
	int	i;

	i = 0;
	if (line)
	{
		while(line[i] != '\0')
		{
			if ((line[i] >= '0') && (line[i] <= '9'))
				data->width++;
			i++;
		}
	}
}

void	read_map(t_data	*data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("assets/map", O_RDONLY);
	line = get_next_line(fd);
	linelen(data, line);
	while (line != NULL)
	{
		// if (check_map(line, data) == 1)
		// {
		// 	perror("Invalid map");
		// 	exit(128);
		// }
		printf("%s", line);
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	// second_parse(data, fd);
}

// void	insert_map(t_data	*data)
// {
// 	int	i;

// 	i = 0;

// }

void	draw(t_data	*data)
{
	int x;
	int	y;

	y = 0;
	x = 0;

	while (y <= data->height)
	{
		x = 0;
		while (x <= data->width)
		{
			mlx_put_pixel(data->image, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	hooking(mlx_key_data_t keydata, void* param)
{
	t_data *data;

	data = param;

if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
	
}

void	bresen(t_data	*data, int	x0, int	y0, int	x1, int	y1)
{
	int	dx;
	int	dy;
	int	error;
	int	x;
	int	y;

	x0 *= data->scale;
	y0 *= data->scale;
	x1 *= data->scale;
	y1 *= data->scale;
	x0 += data->shiftx;
	y0 += data->shifty;
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	error = 2 * (dy - dx);

	printf("X = [%d] Y = [%d] X1 = [%d] Y1 = [%d] Delta X = [%d] Delta Y = [%d] error = [%d]\n",x, y, x1, y1, dx, dy, error);
	while (x <= x1 && y <= y1)
	{
		if (error >= 0)
		{
			mlx_put_pixel(data->image, x, y, 0xFF0000FF);
			y++;
			error = error + 2 * dy - 2 * dx;
		}
		else
		{
			mlx_put_pixel(data->image, x, y, 0xFF0000FF);
			error = error + (2 * dy);
			x++;
		}
	}
	// mlx_image_to_window(data->mlx, data->image, 0, 0);
}

int	main(int argc, char	**argv)
{
	char	*line;
	int		fd;
	int		x;
	int		y;
	t_data	*data;
	mlx_key_data_t keydata;

	setbuf(stdout, NULL);
	data = malloc(sizeof(t_data));
	data->width = 0;
	data->height = 0;
	data->scale = 30;
	read_map(data);
	printf ("height = [%d],width = [%d]\n", data->height, data->width);
	data->mlx = mlx_init(1920, 1080, "FDF", true);
	data->image = mlx_new_image(data->mlx, 1920, 1080);
	// draw (data);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y + 1 < data->height)
				bresen(data, x, y, x, y + 1);
			if (x + 1 < data->width)
				bresen(data, x, y, x + 1, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop(data->mlx);

	return (0);
}
 // first collom then row