/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:57:29 by gde-pass          #+#    #+#             */
/*   Updated: 2018/04/05 16:18:21 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft/includes/libft.h"

typedef struct	s_point
{
	double		x;
	double		y;
	double		height;
}				t_point;

typedef	struct	s_image
{
	int			bpp;
	int			endian;
	int			size_ln;
	void		*ptr_img;
	char		*str_img;
}				t_image;

typedef	struct	s_window
{
	int			width;
	int			height;
	int			tile_wdth;
	int			tile_hght;
}				t_window;

typedef struct	s_modif
{
	int			on;
	int			color;
	double		wdth;
	double		hght;
	double		alt;
	double		zoom;
}				t_modif;

typedef struct	s_mlx
{
	void		*mlx;
	void		*wiw;
	t_point		*pt;
	t_point		*ptbckp;
	t_image		*img;
	t_window	*win;
	t_modif		*modif;
	char		*file;
	int			nb_pt;
	int			nb_ln;
	int			size_ln;
}				t_mlx;

/*
** Init functions
*/

void			init(t_mlx *mlx);

/*
** Check functions
*/

void			check_file(char *str);
void			check_line(t_mlx *mlx);
void			check_extension(t_mlx *mlx);
int				check_fd(t_mlx *mlx, int fd);
void			check_input(t_mlx *mlx, int ac);

/*
** Parsing functions
*/

void			parser(t_mlx *mlx);
char			*file_to_str(t_mlx *mlx, char *str, int fd);
t_point			*str_to_struct(t_mlx *mlx, char *str, int i, int j);
t_point			*malloc_the_struct(t_mlx *mlx, char *str, int nb_pt);

/*
** Drawing, converting and all display functions
*/

void			move_map(t_mlx *mlx);
void			zoom_map(t_mlx *mlx);
void			draw_map(t_mlx *mlx);
void			map_pos_to_screen(t_mlx *mlx);
void			fill_pixel(t_mlx *mlx, int x, int y);
void			draw_line(t_mlx *mlx, t_point pt1, t_point pt2);

/*
** Refresh, running & event functions
*/

void			fdf(t_mlx *mlx);
void			refresh(t_mlx *mlx);
int				key_events(int keycode, t_mlx *mlx);
void			zoom_move_events(int keycode, t_mlx *mlx);

#endif
