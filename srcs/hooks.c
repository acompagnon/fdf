/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:03:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/10 17:29:07 by acompagn         ###   ########.fr       */
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

void		menu_window(t_env *e)
{
	mlx_clear_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 312,
		e->color.white, "ESC         -> exit window\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 327,
		e->color.white, "ENTER       -> clean changes\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 342,
		e->color.white, "n           -> reset line origins\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 357,
		e->color.white, "RIGHT CLICK -> draw line\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 372,
		e->color.white, "LEFT CLICK  -> erase mode\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 332, 392,
		e->color.white, "r           -> go back to map\n");
}

int			key_hook(int key, t_env *e)
{
	printf("key == %d\n", key);
	if (key == 126 || key == 125)
	{
		e->key_126 = (key == 125) ? 0 : 1;
		e->key_125 = (key == 125) ? 1 : 0;
		mlx_clear_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		draw_map(e);
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
	{
		if (e->key_36)
		{
			e->origin_x = -1;
			e->origin_y = -1;
			e->key_126 = 0;
		}
		e->key_36 = 1;
		mlx_clear_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 10,
				e->color.white, "Press o to see options\n");
		draw_map(e);
	}
	return (0);
}

int			mouse_hook(int key, int x, int y, t_env *e)
{
	if (key == 1 && e->origin_x != -1 && e->origin_y != -1)
		draw_line(e, x, y, e->color.red);
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
