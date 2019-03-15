/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 17:07:33 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		compute_center(t_env *e)
{
	int		x;
	int		y;
	t_dot	center;
	t_dot	first;

	center = new_dot(e, e->map_size_y / 2, e->map_size_x / 2);
	first = new_dot(e, e->map_size_y - 1, 0);
	y = center.y - 5;
	while (++y < center.y + 5)
	{
		x = center.x - 5;
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, x, y, YELLOW);
		while (++x < center.x + 5)
			mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, x, y, YELLOW);
	}
	y = first.y - 5;
	while (++y < first.y + 5)
	{
		x = first.x - 5;
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, x, y, RED);
		while (++x < first.x + 5)
			mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, x, y, RED);
	}
	e->camera.center_x = center.x;
	e->camera.center_y = center.y;
}

t_dot		new_dot(t_env *e, int y, int x)
{
	t_dot	dot;
	int		tmp_x;
	int		tmp_y;

	dot.x = x * e->camera.zoom + ((e->iso_key) ? WIN_Y / 1.85 : WIN_X * 1.05);
	dot.y = y * e->camera.zoom - ((e->iso_key) ? WIN_Y / 10 : -(WIN_X / 1.70));
	if (e->camera.zoom_x && e->camera.zoom_y)
	{
		dot.x -= e->camera.zoom_x / 2;
		dot.y -= e->camera.zoom_y / 2;
	}
	dot.x += e->camera.center_x + e->camera.move_x - e->left_click_x;
	dot.y += e->camera.center_y + e->camera.move_y - e->left_click_y;
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
	e->camera.medium_alt = 0;
	e->camera.altitude = 0;
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
	e->mouse_released = 0;
}
