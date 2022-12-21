/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:46:29 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/20 16:00:43 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	bresen_util(t_data	*data, t_draw	*drw,	float	*x1, float *y1)
{
	drw->z = data->map[(int)drw->y][(int)drw->x];
	drw->z1 = data->map[(int)*y1][(int)*x1];
	drw->x *= data->scale;
	drw->y *= data->scale;
	*x1 *= data->scale;
	*y1 *= data->scale;
}

void	bresen_shift(t_data	*data, t_draw	*drw,	float	*x1, float *y1)
{
	drw->x += data->shiftx;
	drw->y += data->shifty;
	*x1 += data->shiftx;
	*y1 += data->shifty;
}

void	bresen_steps(t_draw *drw, float x1, float y1)
{
	drw->x_step = x1 - drw->x;
	drw->y_step = y1 - drw->y;
	drw->max = maximum(fabs(drw->y_step), fabs(drw->x_step));
	drw->x_step /= drw->max;
	drw->y_step /= drw->max;
}

void	bresen(t_data *data, t_draw drw, float x1, float y1)
{
	bresen_util(data, &drw, &x1, &y1);
	if (data->isometric == -1)
	{
		isometric(&drw.x, &drw.y, drw.z, data);
		isometric(&x1, &y1, drw.z1, data);
	}
	bresen_shift(data, &drw, &x1, &y1);
	bresen_steps(&drw, x1, y1);
	while ((int)(drw.x - x1) || (int)(drw.y - y1))
	{
		if ((drw.y < data->img->height && drw.y > 0) && \
			(drw.x < data->img->width && drw.x > 0))
		{
			if (drw.z)
				mlx_put_pixel(data->img, (int)drw.x, (int)drw.y, 0xDA462B);
			else
				mlx_put_pixel(data->img, (int)drw.x, (int)drw.y, 0xA8341F);
		}
		drw.x += drw.x_step;
		drw.y += drw.y_step;
	}
	if ((drw.y < data->img->height && drw.y > 0) && \
	(drw.x < data->img->width && drw.x > 0))
		mlx_put_pixel(data->img, (int)drw.x, (int)drw.y, 0xA8341F);
}

void	draw(t_data	*data)
{
	t_draw	drw;

	drw.y = 0;
	drw.x = 0;
	ft_bzero(data->img->pixels, (data->img->height * data->img->width) \
		* sizeof(unsigned int));
	while (drw.y < data->height)
	{
		drw.x = 0;
		while (drw.x < data->width)
		{
			if (drw.y + 1 < data->height)
				bresen(data, drw, drw.x, drw.y + 1);
			if (drw.x + 1 < data->width)
				bresen(data, drw, drw.x + 1, drw.y);
			drw.x++;
		}
		drw.y++;
	}
}
