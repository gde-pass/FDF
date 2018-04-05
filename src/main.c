/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:12:39 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:12:43 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init(t_mlx *mlx)
{
	mlx->modif->on = 1;
	mlx->modif->alt = 2;
	mlx->modif->wdth = 0;
	mlx->modif->hght = 0;
	mlx->modif->zoom = 0;
	mlx->win->width = 1920;
	mlx->win->height = 1080;
	mlx->win->tile_wdth = 48;
	mlx->win->tile_hght = 48;
	while (((mlx->win->tile_wdth * mlx->size_ln) > mlx->win->width) ||
		((mlx->win->tile_hght * mlx->nb_ln) > mlx->win->height))
	{
		mlx->win->tile_wdth -= 2;
		mlx->win->tile_hght -= 2;
	}
}

void	refresh(t_mlx *mlx)
{
	mlx->img->ptr_img = mlx_new_image(mlx->mlx, mlx->win->width,
		mlx->win->height);
	mlx->img->str_img = mlx_get_data_addr(mlx->img->ptr_img,
		&(mlx->img->bpp), &(mlx->img->size_ln), &(mlx->img->endian));
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->wiw, mlx->img->ptr_img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->ptr_img);
}

void	fdf(t_mlx *mlx)
{
	mlx->wiw = mlx_new_window(mlx->mlx,
		mlx->win->width, mlx->win->height, "FdF");
	refresh(mlx);
	mlx_hook(mlx->wiw, 2, 0, key_events, mlx);
	mlx_loop(mlx->mlx);
}

int		main(int ac, char **av)
{
	t_mlx		*mlx;

	if (!(mlx = malloc(sizeof(t_mlx)))
		|| !(mlx->win = malloc(sizeof(t_window)))
		|| !(mlx->img = malloc(sizeof(t_image)))
		|| !(mlx->modif = malloc(sizeof(t_modif)))
		|| (!(mlx->mlx = mlx_init())))
		exit(EXIT_FAILURE);
	mlx->file = av[1];
	check_input(mlx, ac);
	parser(mlx);
	init(mlx);
	fdf(mlx);
}
