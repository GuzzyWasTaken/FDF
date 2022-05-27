#ifndef FDF_H
# define FDF_H

# include "../MLX_42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				height;
	int				width;
	int				**map;
	int				error;
	int				scale;
	int				shiftx;
	int				shifty;
}	t_data;


char	*get_next_line(int fd);                                                                                                                                                                                                                                                                                                                                       
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strchr(const char *src, int c);
char	*ft_strdup(char *s);



#endif
