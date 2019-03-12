/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:03:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/12 19:23:51 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_hook(int key, t_env *e)
{
	if (key == 34 || key == 35)
	{
		e->key_34 = (key == 35) ? 0 : 1;
		restart(e);
	}
	else if (key == 53 || key == 8)
	{
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		free_env(e, NULL, 1);
	}
	else if (key == 45)
	{
		e->origin_x = -1;
		e->origin_y = -1;
	}
	else if (key == 31)
		menu_window(e);
	else if (key == 36 || key == 15)
		restart(e);
	return (0);
}

int			mouse_hook(int key, int x, int y, t_env *e)
{
	if (key == 1 && e->origin_x != -1 && e->origin_y != -1)
	{
		draw_line(e, new_line(e->origin_y, e->origin_x), new_line(y, x), RED);
		mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
	}
	if (key == 2 || e->mouse_released)
	{
		e->mouse_released = 1;
		erase_zone(e, x, y);
	}
	if (e->key_36)
	{
		e->origin_x = (e->origin_x == -1) ? x : e->origin_x;
		e->origin_y = (e->origin_y == -1) ? y : e->origin_y;
	}
	return (0);
}

int			holding_key(int key, t_env *e)
{
	(key == 7) ? e->camera.rot_x += 0.01 : 1;
	(key == 16) ? e->camera.rot_y += 0.01 : 1;
	(key == 123) ? e->camera.rot_z -= 0.01 : 1;
	(key == 124) ? e->camera.rot_z += 0.01 : 1;
	(key == 125) ? e->camera.altitude-- : 1;
	(key == 126) ? e->camera.altitude++ : 1;
	draw_map(e);
	return (0);
}

int			motion_hook(int x, int y, t_env *e)
{
	if (e->mouse_released)
		erase_zone(e, x, y);
	return (0);
}

int			test_hook(int key, int x, int y,  t_env *e)
{
	e->mouse_released = 0;
	(void)key;
	(void)x;
	(void)y;
	return (0);
}
