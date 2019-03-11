/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:08:27 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 19:05:00 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		restart(t_env *e)
{
	if (e->key_36)
	{
		e->origin_x = -1;
		e->origin_y = -1;
		e->camera.altitude = 0;
		e->camera.rot_x = 0.0;
		e->camera.rot_y = 0.0;
		e->camera.rot_z = 0.0;
	}
	e->key_36 = 1;
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
				erase_y, 0x000000);
		while (erase_x++ < x + 10)
			mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, erase_x,
					erase_y, 0x000000);
	}
}

void		clean_window(t_env *e)
{
	e->mlx.img_ptr ? free(e->mlx.img_ptr) : 1;
	if (!(e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, 1000, 750)))
		free_env(e, NULL, 1);
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp,
			&e->mlx.s_l, &e->mlx.endian);
}
