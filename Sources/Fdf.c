/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fdf.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: auzochuk <auzochuk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 09:01:09 by auzochuk      #+#    #+#                 */
/*   Updated: 2022/12/12 18:28:00 by auzochuk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// void	check_file(char	*av)
// {
// 	int	len;

// 	len = ft_strlen(av);

// 	if(!str)
// 	{
// 		write(2, "invalid file\n", 14);
// 		exit (0);
// 	}
// }

int	main(int argc, char	**argv)
{
	if (argc != 2)
		exit (0);
	// check_file(argv[1]);
	init_data(argv);
	// while (1)
	// 	;
	// system("leaks fdf");
	return (0);
}

//if no arg, segfault