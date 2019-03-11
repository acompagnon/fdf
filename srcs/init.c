/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 19:16:34 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot		new_line(int y, int x)
{
	t_dot	dot;

	dot.x = x;
	dot.y = y;
	dot.z = 0;
	return (dot);
}

t_dot		new_dot(t_env *e, int y, int x)
{
	t_dot	dot;

	dot.x = x * e->camera.zoom + 400;
	dot.y = y * e->camera.zoom - 50;
	if ((dot.z = e->map_tab[y][x]))
		dot.z += e->camera.altitude;
	return (dot);
}

void		init(t_env *e)
{
	e->map = NULL;
	e->map_tab = NULL;
	e->map_size_y = 0;
	e->map_size_x = 0;
	e->key_36 = 0;
	e->camera.zoom = 30;
	e->camera.altitude = 0;
	e->camera.rot_x = 0.00;
	e->camera.rot_y = 0.00;
	e->camera.rot_z = 0.00;
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
	e->mouse_released = 0;
}
