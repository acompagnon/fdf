/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_restart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:40:40 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 19:15:12 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		move_image_to(t_env *e, int x, int y)
{
	e->camera.move_x = x;
	e->camera.move_y = y;
	draw_map(e);
}

void		restart(t_env *e)
{
	if (e->key.enter)
	{
		find_zoom(e);
		e->camera.altitude = 0;
		e->camera.move_x = 0;
		e->camera.move_y = 0;
	}
	e->key.enter = 1;
	draw_map(e);
}

void		erase_zone(t_env *e, int x, int y)
{
	int		erase_x;
	int		erase_y;

	erase_x = x - 10;
	erase_y = y - 10;
	while (erase_y++ < y + 10)
	{
		erase_x = x - 10;
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, erase_x,
				erase_y, BLACK);
		while (erase_x++ < x + 10)
			mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, erase_x,
					erase_y, BLACK);
	}
}

void		clean_window(t_env *e)
{
	e->mlx.img_ptr ? free(e->mlx.img_ptr) : 1;
	if (!(e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, WIN_X, WIN_Y)))
		free_env(e, NULL, 1);
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp,
			&e->mlx.s_l, &e->mlx.endian);
}
