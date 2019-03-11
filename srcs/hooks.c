/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:03:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 17:39:40 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp, &e->mlx.s_l, &e->mlx.endian);
}

void		menu_window(t_env *e)
{
	clean_window(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr, e->mlx.img_ptr, 0, 0);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 312,
		WHITE, "ESC         -> exit window\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 327,
		WHITE, "ENTER       -> clean changes\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 342,
		WHITE, "n           -> reset line origins\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 357,
		WHITE, "RIGHT CLICK -> draw line\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 372,
		WHITE, "LEFT CLICK  -> erase mode\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 392,
		WHITE, "r           -> go back to map\n");
}

void		restart_hooks(t_env *e)
{
	if (e->key_36)
	{
		e->origin_x = -1;
		e->origin_y = -1;
		e->camera.altitude = 0;
	}
	e->key_36 = 1;
	draw_map(e);
}

void		camera_hooks(t_env *e, int key)
{
	(key == 125) ? e->camera.altitude-- : 1;
	(key == 126) ? e->camera.altitude++ : 1;
	(key == 7) ? e->camera.rot_x += 0.01 : 1;
	(key == 16) ? e->camera.rot_y += 0.01 : 1;
	(key == 6) ? e->camera.rot_z += 0.01 : 1;
	draw_map(e);
}

int			key_hook(int key, t_env *e)
{
//	printf("key = %d\n", key);
	if (key == 126 || key == 125 || key == 7 || key == 6 || key == 16)
		camera_hooks(e, key);
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
		restart_hooks(e);
	return (0);
}

int			mouse_hook(int key, int x, int y, t_env *e)
{
	if (key == 1 && e->origin_x != -1 && e->origin_y != -1)
		draw_line(e, new_line(e->origin_y, e->origin_x), new_line(y, x), RED);
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
