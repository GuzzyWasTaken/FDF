/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fdf.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 09:01:09 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/21 08:54:44 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>

void	check_file(char	*av)
{
	int	len;

	len = ft_strlen(av);
	if (!len)
	{
		write(2, "invalid file\n", 14);
		exit (0);
	}
	if (ft_strncmp(av + (len - 4), ".fdf", 4) != 0)
	{
		write(2, "invalid file: make sure file is a .fdf file\n", 44);
		exit (0);
	}
}

int	main(int argc, char	**argv)
{
	if (argc != 2)
		exit (0);
	check_file(argv[1]);
	init_data(argv);
	return (0);
}
