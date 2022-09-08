#include <stdio.h>
#include "../includes/fdf.h"
#include <math.h>


void insert(char *line, t_data *data, int	height)
{
	char	**array;
	int	i;
	int x;

	x = 0;
	i = 0;

	// printf("line: %s\n", line);
	// printf("made it\n");
	x++;
	array = ft_split(line, ' ');
	while(array[i])
	{
		data->map[height][i] = ft_atoi(array[i]);
		// printf("%d ", data->map[height][i]);
		i++;
	}
	free (array);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
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
	fd = open("assets/map2", O_RDONLY);
	line = get_next_line(fd);
	// array = ft_split(line, ' ');
	insert(line, data, i);
	// printf("line: %s\n", line);
	i++;
	// printf("test\n");
	while (i < data->height)
	{
		// free(array);
		// printf("safety check\n");
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
	fd = open("assets/map2", O_RDONLY);
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

float maximum(float	y, float	x)
{
	if (y > x)
		return(y);
	return (x);
}

void bresen(t_data	*data, float x, float y, float x1, float y1)
{

	float	x_step;
	float	y_step;
	float	max;
	int		z;
	int		z1;


	printf("[%f]%f\n", x, y);
	z = data->map[(int)y][(int)x];
	z1 = data->map[(int)y1][(int)x1];

	x += data->shiftx;
	y += data->shifty;
	x1 += data->shiftx;
	y1 += data->shifty;
	x *= data->scale;
	y *= data->scale;
	x1 *= data->scale;
	y1 *= data->scale;

	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);

	x_step = x1 - x;
	y_step = y1 - y;
	max = maximum(fabs(y_step), fabs(x_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		if ((y < data->image->height && y > 0) && (x < data->image->width && x > 0))
			mlx_put_pixel(data->image, (int)x, (int)y, 0xfffffffff);
		x += x_step;
		y += y_step;
	}
}


void	draw(t_data	*data)
{
	int x;
	int	y;

	y = 0;
	ft_bzero(data->image->pixels, (data->mlx->height * data->mlx->width) * sizeof(unsigned int));
	x = (x - y);
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
	if (keydata.key == MLX_KEY_E)
	{
		data->isometric *= -1;
		printf("iso = %i\n", data->isometric);
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
	data->isometric = -1;
	read_map(data);
	// printf("\nwidth: %i height: %i\n", data->width, data->height);
	// while (y < data->height)
	// {
	// 	while (x < data->width)
	// 	{
	// 		printf("[%i][%i] = %d ", y, x, data->map[y][x]);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	write(1, "\n", 1);
	// 	y++;
	// }
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