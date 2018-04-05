/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:12:24 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:12:28 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_map(t_mlx *mlx)
{
	int i;

	i = 0;
	while (mlx->pt[i].x != -1 && i <= mlx->nb_pt)
	{
		mlx->pt[i].x += mlx->modif->wdth;
		mlx->pt[i].y += mlx->modif->hght;
		if (mlx->pt[i].height != 0)
			mlx->pt[i].y -= mlx->modif->alt;
		i++;
	}
	refresh(mlx);
}

void	zoom_map(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->pt[i].x != -1 && i <= mlx->nb_pt)
	{
		mlx->pt[i].x *= (mlx->modif->zoom);
		mlx->pt[i].y *= (mlx->modif->zoom);
		i++;
	}
	refresh(mlx);
}

void	fill_pixel(t_mlx *mlx, int x, int y)
{
	if (((y * (mlx->img->size_ln)) + (4 * x) + 2) > (y * (mlx->img->size_ln))
		&& ((y * (mlx->img->size_ln)) + (4 * x) + 2) > 0
		&& ((y * (mlx->img->size_ln)) + (4 * x) + 2) <
		(4 * mlx->win->width * mlx->win->height)
		&& ((y * (mlx->img->size_ln)) + (4 * x) + 2) <
		((y + 1)) * (mlx->img->size_ln))
	{
		mlx->img->str_img[(y * (mlx->img->size_ln)) + (4 * x)] = 0xD1;
		mlx->img->str_img[(y * (mlx->img->size_ln)) + (4 * x) + 1] = 0x99;
		mlx->img->str_img[(y * (mlx->img->size_ln)) + (4 * x) + 2] = 0x2E;
	}
}

void	draw_line(t_mlx *mlx, t_point pt1, t_point pt2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = 0;
	x = pt1.x;
	dx = pt2.x - pt1.x;
	dy = pt2.y - pt1.y;
	while (x < pt2.x)
	{
		y = pt1.y + dy * (x - pt1.x) / dx;
		fill_pixel(mlx, x, y);
		x++;
	}
}

void	draw_map(t_mlx *mlx)
{
	int		i;

	i = 0;
	if (mlx->modif->on == 1)
		map_pos_to_screen(mlx);
	while (mlx->pt[i].x != -1 && i <= mlx->nb_pt)
	{
		if (mlx->nb_ln == 1 && i < mlx->nb_pt)
			draw_line(mlx, mlx->pt[i], mlx->pt[i + 1]);
		if (i < mlx->nb_pt)
			draw_line(mlx, mlx->pt[i], mlx->pt[i + 1]);
		if (i + mlx->size_ln < mlx->nb_pt && !(i % mlx->size_ln == 0
			&& mlx->pt[i + 1].x == 0) && mlx->pt[i + 1].x != 1)
			draw_line(mlx, mlx->pt[i + mlx->size_ln], mlx->pt[i]);
		i++;
	}
}
