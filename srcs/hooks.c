/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:03:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/16 20:01:37 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_hook(int key, t_env *e)
{
	if (key == 34 || key == 35)
	{
		e->key.iso = (key == 35) ? 0 : 1;
		restart(e);
	}
	else if (key == 53 || key == 8)
	{
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		free_env(e, NULL, 1);
	}
	else if (key == 31)
	{
		menu_window(e);
		e->menu_mode = 1;
	}
	else if ((key == 36 && !e->menu_mode) || (key == 15 && e->menu_mode))
	{
		e->menu_mode = 0;
		restart(e);
	}
	return (0);
}

int			mouse_hook(int key, int x, int y, t_env *e)
{
	if (e->menu_mode && key == 1)
		choose_color(e, x, y);
	if (!e->menu_mode && (key == 2 || key == 1 || e->key.mouse_released))
	{
		e->key.left_click = (key == 2) ? 0 : 1;
		(e->key.left_click) ? e->key.left_click_x = x : 1;
		(e->key.left_click) ? e->key.left_click_y = y : 1;
		e->key.mouse_released = 1;
	}
	if (!e->menu_mode && (key == 5 || key == 4))
	{
		if (key == 5)
			e->camera.zoom += 1.5;
		else if (e->camera.zoom - 1.5 > 0)
			e->camera.zoom -= 1.5;
		e->camera.zoom_x = x;
		e->camera.zoom_y = y;
		draw_map(e);
	}
	return (0);
}

int			holding_key(int key, t_env *e)
{
	if (!e->menu_mode)
	{
		(key == 125) ? e->camera.altitude-- : 1;
		(key == 126) ? e->camera.altitude++ : 1;
		(key == 7) ? e->rot_x += 0.1 : 1;
		(key == 6) ? e->rot_z += 0.1 : 1;
		(key == 16) ? e->rot_y += 0.1 : 1;
		draw_map(e);
	}
	return (0);
}

int			motion_hook(int x, int y, t_env *e)
{
	if (e->key.enter && !e->menu_mode && e->key.mouse_released)
		e->key.left_click ? move_image_to(e, x, y) : erase_zone(e, x, y);
	return (0);
}

int			release_hook(int key, int x, int y, t_env *e)
{
	e->key.mouse_released = 0;
	(void)key;
	(void)x;
	(void)y;
	return (0);
}
