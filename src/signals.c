/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:13:37 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:13:40 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key_events(int keycode, t_mlx *mlx)
{
	mlx->modif->on = 0;
	mlx->modif->alt = 1;
	mlx->modif->wdth = 0;
	mlx->modif->hght = 0;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 71)
	{
		free(mlx->pt);
		parser(mlx);
		init(mlx);
		mlx->pt = mlx->ptbckp;
		refresh(mlx);
	}
	zoom_move_events(keycode, mlx);
	return (0);
}

void	zoom_move_events(int keycode, t_mlx *mlx)
{
	if (keycode >= 116 && keycode <= 126)
	{
		if (keycode == 123)
			mlx->modif->wdth -= 50;
		if (keycode == 124)
			mlx->modif->wdth += 50;
		if (keycode == 125)
			mlx->modif->hght += 50;
		if (keycode == 126)
			mlx->modif->hght -= 50;
		if (keycode == 116)
			mlx->modif->alt *= 0.5;
		if (keycode == 121)
			mlx->modif->alt *= -0.5;
		move_map(mlx);
	}
	if (keycode == 69 || keycode == 78)
	{
		mlx->modif->zoom = 1;
		if (keycode == 69)
			mlx->modif->zoom += 0.5;
		if (keycode == 78)
			mlx->modif->zoom -= 0.5;
		zoom_map(mlx);
	}
}
