#include <stdio.h>
#include "../includes/fdf.h"


void insert(char *line, t_data *data, int	height)
{
	char	**array;
	int	i;
	int x;

	x = 0;
	i = 0;

	printf("line: %s\n", line);
	printf("made it\n");
	x++;
	array = ft_split(line, ' ');
	while(array[i])
	{
		data->map[height][i] = ft_atoi(array[i]);
		printf("line in insert: %d\n", data->map[height][i]);
		i++;
	}
	free (array);
} 

void	second_parse(t_data	*data)
{
	int		height;
	int		width;
	char	*line;
	// char	**array;
	int		i;
	int		x;
	int		fd;

	i = 0;
	height = 0;
	width = 0;
	x = 0;
	data->map = malloc(data->height * sizeof(int *));
	while(height < data->height)
	{
		data->map[height] = ft_calloc((data->width + 1), sizeof(int));
		// printf ("map00 = %d\n", data->map[0][0]);
		height++;
	}
	fd = open("assets/map", O_RDONLY);
	line = get_next_line(fd);
	// array = ft_split(line, ' ');
	insert(line, data, i);
	printf("line: %s\n", line);
	i++;
	printf("test\n");
	while (i < data->height)
	{
		// free(array);
		printf("safety check\n");
		line = get_next_line(fd);
		insert(line, data, i);
		// printf("array: %s\n", array[x]);
		free(line);
		i++;
	}
}


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
	close(fd);
	if (line)
		free(line);
	second_parse(data);
}

void	bresen(t_data	*data, int	x0, int	y0, int	x1, int	y1)
{
	int	dx;
	int	dy;
	int	error;
	int	x;
	int	y;

	x0 += data->shiftx;
	y0 += data->shifty;
	x1 += data->shiftx;
	y1 += data->shifty;
	x0 *= data->scale;
	y0 *= data->scale;
	x1 *= data->scale;
	y1 *= data->scale;
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	error = 2 * (dy - dx);

//	printf("X = [%d] Y = [%d] X1 = [%d] Y1 = [%d] Delta X = [%d] Delta Y = [%d] error = [%d]\n",x, y, x1, y1, dx, dy, error);
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
}

void	draw(t_data	*data)
{
	int x;
	int	y;

	y = 0;
	ft_bzero(data->image->pixels, (data->mlx->height * data->mlx->width) * sizeof(unsigned int));

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

}

void	hooking(mlx_key_data_t keydata, void* param)
{
	t_data *data;

	data = param;
	
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_D)
	{
		data->shiftx = data->shiftx + 1;
		draw(data);
	}
	if (keydata.key == MLX_KEY_S)
	{
		data->shifty = data->shifty + 1;
		draw(data);
	}

	if (keydata.key == MLX_KEY_W)
	{
		data->shifty = data->shifty - 1;
		draw(data);
	}
	if (keydata.key == MLX_KEY_A)
	{
		data->shiftx = data->shiftx - 1;
		draw(data);
	}
	//printf("x = [%d], y = [%d]\n", data->shiftx, data->shifty);
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
	data = calloc(sizeof(t_data),1);
	data->width = 0;
	data->height = 0;
	data->scale = 30;
	data->shiftx = 0;
	data->shifty = 0;
	read_map(data);
//	printf ("height = [%d],width = [%d]\n", data->height, data->width);
	// printf ("%d", data->map[3][9]);
	data->mlx = mlx_init(1920, 1080, "FDF", true);
	data->image = mlx_new_image(data->mlx, 1920, 1080);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	draw (data);
	mlx_key_hook(data->mlx, &hooking, data);
	mlx_loop(data->mlx);

	return (0);
}
 // first collom then row