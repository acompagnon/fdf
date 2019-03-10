/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:33:02 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/10 17:29:01 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		compute_medium_distance(t_env *e)
{
	e->distance_x = 500 / e->map_size_x;
	e->distance_y = 500 / e->map_size_y;
}

void		y_matrix(t_env *e, int i, int j, int color)
{
	int		tmp_x;
	int		tmp_y;
	int		relief;

	tmp_x = e->origin_x;
	tmp_y = e->origin_y;
	if (e->key_126)
		e->map_tab[i][j] += 3;
	if (e->key_125)
		e->map_tab[i][j] -= 3;
	relief = e->map_tab[i][j];
	draw_line(e, e->origin_x + e->distance_x, e->origin_y - relief, e->color.blue);
	if (j + 1 < e->map_size_x && e->map_tab[i][j + 1])
	draw_line(e, e->origin_x, e->origin_y - e->distance_y, color);
	e->origin_y -= e->distance_y;
	draw_line(e, e->origin_x + e->distance_x, e->origin_y - relief, e->color.yellow);
	e->origin_x += e->distance_x;
	draw_line(e, e->origin_x, e->origin_y - relief, e->color.green);
	draw_line(e, e->origin_x, e->origin_y + e->distance_y - relief, e->color.green);
	e->origin_x = tmp_x;
	e->origin_y = tmp_y;
}
void		draw_map(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	e->origin_y = 143;
	compute_medium_distance(e);
	while (++i < e->map_size_y)
	{
		j = -1;
		e->origin_x = 252;
		while (++j < e->map_size_x)
		{
			if (e->map_tab[i][j])
				y_matrix(e, i, j, e->color.green);
		/*	draw_line(e, e->origin_x + e->distance_x, e->origin_y, e->color.yellow); // trace de gauche a droite
			if (i + 1 < e->map_size_y)
				draw_line(e, e->origin_x, e->origin_y + e->distance_y, e->color.yellow); // trace de haut en bas*/
			e->origin_x = e->origin_x + e->distance_x;
		}
	/*	if (i + 1 < e->map_size_y)
			draw_line(e, e->origin_x, e->origin_y + e->distance_y, e->color.yellow); // trace de haut en bas*/
		e->origin_y = e->origin_y + e->distance_y;
	}
	e->origin_x = -1;
	e->origin_y = -1;
}

void		mlx_call(t_env *e)
{
	if (!(e->mlx.mlx_ptr = mlx_init()))
		free_env(e, NULL, 1);
	if (!(e->mlx.win_ptr = mlx_new_window(e->mlx.mlx_ptr, 1000, 750, "FDF")))
		free_env(e, NULL, 1);
	if (!(e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, 1000, 750)))
		free_env(e, NULL, 1);
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp,
			&e->mlx.s_l, &e->mlx.endian);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 395, 335,
			e->color.white, "PRESS ENTER TO START\n");
	mlx_key_hook(e->mlx.win_ptr, key_hook, e);
	mlx_hook(e->mlx.win_ptr, 5, 1L<<3, test_hook, e);
	mlx_hook(e->mlx.win_ptr, 6, 1L<<6, motion_hook, e);
	mlx_mouse_hook(e->mlx.win_ptr, mouse_hook, e);
	mlx_loop(e->mlx.mlx_ptr);
}
