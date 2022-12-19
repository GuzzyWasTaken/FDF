/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 08:47:29 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/19 14:00:57 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX_42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include  <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_draw
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	float	max;
	int		z;
	int		z1;
}	t_draw;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			*arg_map;
	int				height;
	int				width;
	int				**map;
	int				error;
	int				scale;
	int				shiftx;
	int				shifty;
	int				isometric;
	float			angle;
}	t_data;

char	*get_next_line(int fd);
char	*gn_substr(char *s, unsigned int start, size_t len);
size_t	gn_strlen(const char *s);
char	*gn_calloc(size_t count, size_t size);
char	*gn_strjoin(char *s1, char const *s2);
int		gn_strchr(const char *src, int c);
char	*gn_strdup(char *s);
void	init_data(char **argv);
void	map_height(int height, t_data *data);
void	insert(char *line, t_data *data, int height);
void	read_map(t_data	*data);
void	draw(t_data	*data);
void	fdf_free(char	**str);
void	bresen(t_data *data, t_draw drw, float x1, float y1);
void	isometric(float *x, float *y, int z, t_data *data);
float	maximum(float y, float x);

#endif
