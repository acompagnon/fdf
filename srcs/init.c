/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 17:46:27 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_alt_var(int *i, int *count1, int *count2, int *alt_tmp)
{
	*i = -1;
	*count1 = 0;
	*count2 = 0;
	*alt_tmp = 0;
}

t_dot		new_dot(t_env *e, int y, int x)
{
	t_dot	dot;
	int		tmp_x;
	int		tmp_y;

	dot.x = x * e->camera.zoom + ((e->iso_key) ? WIN_Y / 1.85 : WIN_X * 1.05);
	dot.y = y * e->camera.zoom - ((e->iso_key) ? WIN_Y / 10 : -(WIN_X / 1.70));
	camera_moves(e, &dot.x, &dot.y);
	tmp_x = dot.x;
	tmp_y = dot.y;
	if ((dot.z = e->map_tab[y][x]) && dot.z != e->camera.medium_alt)
		dot.z += e->camera.altitude + e->camera.zoom;
	dot.x = (tmp_x - tmp_y) * cos(0.523599);
	if (!e->iso_key)
		dot.y = -dot.z + tmp_y * sin(0.523599);
	else
		dot.y = -dot.z + (tmp_x + tmp_y) * sin(0.523599);
	return (dot);
}

void		init(t_env *e)
{
	e->map = NULL;
	e->map_tab = NULL;
	e->map_size_y = 0;
	e->map_size_x = 0;
	e->iso_key = 1;
	e->key_36 = 0;
	e->menu_mode = 0;
	e->camera.zoom = 0;
	e->camera.zoom_x = 0;
	e->camera.zoom_y = 0;
	e->camera.move_x = 0;
	e->camera.move_y = 0;
	e->camera.medium_alt = 0;
	e->camera.altitude = 0;
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
	e->mouse_released = 0;
}
