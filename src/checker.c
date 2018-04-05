/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:11:57 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:12:12 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_file(char *str)
{
	int i;

	i = 0;
	if (ft_strlen(str) == 0)
	{
		ft_putstr("Empty file, please enter a non empty one.\n");
		exit(EXIT_FAILURE);
	}
}

void	check_extension(t_mlx *mlx)
{
	int	i;
	int true;

	i = 0;
	true = 0;
	while (mlx->file[i])
	{
		if (mlx->file[i] == '.')
		{
			if (mlx->file[i + 1] == 'f' && mlx->file[i + 2] == 'd'
				&& mlx->file[i + 3] == 'f')
				true = 1;
			else
				true = 0;
		}
		i++;
	}
	if (true == 0)
	{
		ft_putstr("Wrong file extension. Enter a valid one please.\n");
		ft_putstr("This way: map.fdf\n");
		exit(EXIT_FAILURE);
	}
}

void	check_input(t_mlx *mlx, int ac)
{
	if (ac < 2)
	{
		ft_putstr("Enter a map parameter, please\n");
		exit(EXIT_FAILURE);
	}
	else if (ac > 2)
	{
		ft_putstr("You've entered too many parameters, just two, please.\n");
		exit(EXIT_FAILURE);
	}
	check_extension(mlx);
}

int		check_fd(t_mlx *mlx, int fd)
{
	fd = open(mlx->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Inexistant or wrong file, enter a valid one, please.\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_line(t_mlx *mlx)
{
	int	i;
	int	szln;

	i = 0;
	szln = mlx->size_ln;
	while (mlx->pt[i + 1].x != -1)
	{
		if (i > 0 && ((i % szln) == szln - 1)
			&& (mlx->pt[i + 1].x != 0))
		{
			ft_putstr("Wrong number of points per line.");
			ft_putstr(" Enter a valid map, please.\n");
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
}
