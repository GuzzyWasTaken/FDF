/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:46:35 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/12 13:00:01 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	hooking_help(mlx_key_data_t keydata, t_data	*data)
{
	if (keydata.key == MLX_KEY_A)
	{
		data->shiftx = data->shiftx - 30;
		draw(data);
	}
	if (keydata.key == MLX_KEY_E)
	{
		data->isometric *= -1;
		draw(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}

void	hooking(mlx_key_data_t keydata, void* param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_D)
	{
		data->shiftx = data->shiftx + 30;
		draw(data);
	}
	if (keydata.key == MLX_KEY_S)
	{
		data->shifty = data->shifty + 30;
		draw(data);
	}
	if (keydata.key == MLX_KEY_W)
	{
		data->shifty = data->shifty - 30;
		draw(data);
	}
	hooking_help(keydata, data);
}

mlx_resizefunc	resize(int width, int height,	void *param)
{
	t_data	*data;

	data = param;
	mlx_resize_image(data->img, width, height);
	ft_bzero(data->img->pixels, (height * width) * sizeof(unsigned int));
	data->shiftx = (width / 2) - (data->width * data->scale / 2);
	data->shifty = (height / 2) - (data->height * data->scale / 2);
	draw(data);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init(1920, 1080, "FDF", true);
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	data->shiftx = (data->mlx->width / 2) - \
	(data->width * data->scale / 2) + 120;
	data->shifty = (data->mlx->height / 2) - (data->height * data->scale / 2);
	draw (data);
	mlx_key_hook(data->mlx, &hooking, data);
	mlx_resize_hook(data->mlx, &resize, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	return (0);
}

int	init_data(char **argv)
{
	t_data			*data;
	mlx_key_data_t	keydata;

	data = calloc(sizeof(t_data), 1);
	data->arg_map = argv[1];
	data->width = 0;
	data->height = 0;
	data->scale = 30;
	data->isometric = -1;
	data->angle = 0.8;
	read_map(data);
	printf("h = %i, w = %i\n",data->height, data->width);
	init_mlx(data);
	return (0);
}