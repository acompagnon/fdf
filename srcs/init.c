/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/16 20:25:09 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		choose_color(t_env *e, int x, int y)
{
	int		base_x;
	int		base_y;
	int		color_place;

	base_y = WIN_Y / 2;
	base_x = WIN_X / 2.75 + 10;
	color_place = 0;
	while (color_place <= 125)
	{
		if (y >= base_y - 75 - 10 && y <= base_y - 75 + 10
			&& x >= base_x + color_place - 10 && x <= base_x + color_place + 10)
			e->color1 = color(color_place);
		else if (y >= base_y - 125 - 10 && y <= base_y - 125 + 10
			&& x > base_x + color_place - 10 && x <= base_x + color_place + 10)
			e->color2 = color(color_place);
		color_place += 25;
	}
}

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

	dot.x = (x - 0.5 * e->map_size_x) * e->camera.zoom;
	dot.y = (y - 0.5 * e->map_size_y) * e->camera.zoom;
	camera_moves(e, &dot.x, &dot.y);
	tmp_x = dot.x;
	tmp_y = dot.y;
	if ((dot.z = e->map_tab[y][x]) && dot.z != e->camera.medium_alt)
		dot.z += e->camera.altitude * e->map_tab[y][x];
	dot.x = (tmp_x - tmp_y) * cos(0.523599);
	dot.y = -dot.z + ((!e->key.iso) ? tmp_y : tmp_x + tmp_y) * sin(0.523599);
	rotate_x(e, &dot.y, &dot.z);
	rotate_y(e, &dot.x, &dot.z);
	rotate_z(e, &dot.x, &dot.y);
	if (!e->camera.move_x && !e->camera.move_y)
	{
		dot.x += WIN_X / 2;
		dot.y += WIN_Y / 2;
	}
	return (dot);
}

void		init_structs(t_env *e)
{
	e->map = NULL;
	e->map_tab = NULL;
	e->map_size_y = 0;
	e->map_size_x = 0;
	e->rot_x = 0;
	e->rot_y = 0;
	e->rot_z = 0;
	e->color1 = BLUE;
	e->color2 = YELLOW;
	e->key.space = 0;
	e->key.iso = 1;
	e->key.enter = 0;
	e->key.mouse_released = 0;
	e->menu_mode = 0;
	e->camera.zoom = 0;
	e->camera.zoom_x = 0;
	e->camera.zoom_y = 0;
	e->camera.move_x = 0;
	e->camera.move_y = 0;
	e->camera.medium_alt = 0;
	e->camera.altitude = 0;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
}
