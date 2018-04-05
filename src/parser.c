/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:12:57 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:13:01 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*file_to_str(t_mlx *mlx, char *str, int fd)
{
	char	*buf;

	fd = check_fd(mlx, fd);
	buf = ft_strnew(BUFF_SIZE);
	str = ft_strnew(BUFF_SIZE);
	while (read(fd, buf, BUFF_SIZE) > 0)
		str = ft_strjoin(str, buf);
	check_file(str);
	close(fd);
	free(buf);
	return (str);
}

t_point	*malloc_the_struct(t_mlx *mlx, char *str, int nb_pt)
{
	int	i;

	i = 0;
	nb_pt = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			nb_pt++;
			while (ft_isprint(str[i]) && !(ft_isspace(str[i])))
				i++;
		}
		if (str[i])
			i++;
	}
	if (!(mlx->pt = malloc(sizeof(t_point) * (nb_pt + 1))))
		return (NULL);
	return (mlx->pt);
}

t_point	*str_to_struct(t_mlx *mlx, char *str, int i, int j)
{
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			mlx->pt[j].x = mlx->nb_pt++;
			mlx->pt[j].y = mlx->nb_ln;
			mlx->pt[j].height = ft_atoi(&str[i]);
			j++;
			while (ft_isprint(str[i]) && !(ft_isspace(str[i])))
				i++;
		}
		if (str[i] == '\n')
		{
			mlx->nb_pt = 0;
			mlx->nb_ln++;
		}
		if (str[i])
			i++;
	}
	mlx->pt[j].x = -1;
	return (mlx->pt);
}

void	parser(t_mlx *mlx)
{
	int		i;
	int		j;
	int		fd;
	char	*str;

	i = 0;
	j = 0;
	fd = 0;
	str = NULL;
	mlx->nb_pt = 0;
	mlx->nb_ln = 1;
	str = file_to_str(mlx, str, fd);
	mlx->pt = malloc_the_struct(mlx, str, i);
	mlx->pt = str_to_struct(mlx, str, i, j);
	while (mlx->pt[i].x != -1)
		i++;
	mlx->nb_pt = i;
	i = 1;
	while (mlx->pt[i].x != 0 && mlx->pt[i].x != -1)
		i++;
	mlx->size_ln = i;
	check_line(mlx);
	mlx->ptbckp = mlx->pt;
	free(str);
}

void	map_pos_to_screen(t_mlx *mlx)
{
	int i;
	int	isox;
	int	isoy;

	i = 0;
	isox = 0;
	isoy = 0;
	while (mlx->pt[i].x != -1)
	{
		isox = (mlx->pt[i].x - mlx->pt[i].y) * (mlx->win->tile_wdth / 2);
		isoy = ((mlx->pt[i].x + mlx->pt[i].y) * (mlx->win->tile_hght / 2))
			- (mlx->pt[i].height * mlx->modif->alt);
		mlx->pt[i].x = isox + (mlx->win->width / 2);
		mlx->pt[i].y = isoy + (mlx->win->tile_hght * 2);
		i++;
	}
}
