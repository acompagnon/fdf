/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:33:02 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/08 17:18:45 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			abs_value(int nb)
{
	return ((nb < 0) ? -nb : nb);
}

void		draw_before(t_env *e, int x, int y)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dx / 2;
	tmp_x = e->origin_x;
	tmp_y = e->origin_y;
	while (i <= e->dx)
	{
		(x - e->origin_x > 0) ? tmp_x++ : tmp_x--;
		cumul += e->dy;
		if (cumul >= e->dx)
		{
			cumul -= e->dx;
			(y - e->origin_y > 0) ? tmp_y++ : tmp_y--;
		}
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
				tmp_y, e->mlx.color);
		i++;
	}
}

void		draw_after(t_env *e, int x, int y)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dy / 2;
	tmp_x = e->origin_x;
	tmp_y = e->origin_y;
	while (i <= e->dy)
	{
		(y - e->origin_y > 0) ? tmp_y++ : tmp_y--;
		cumul += e->dx;
		if (cumul >= e->dy)
		{
			cumul -= e->dy;
			(x - e->origin_x > 0) ? tmp_x++ : tmp_x--;
		}
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
				tmp_y, e->mlx.color);
		i++;
	}
}

void		draw_line(t_env *e, int x, int y)
{
	e->dx = abs_value(x - e->origin_x);
	e->dy = abs_value(y - e->origin_y);
	mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->origin_x,
			e->origin_y, e->mlx.color);
	if (e->dx > e->dy)
		draw_before(e, x, y);
	else
		draw_after(e, x, y);
}

void		compute_medium_distance(t_env *e)
{
	e->distance_x = 500 / e->map_size_x;
	e->distance_y = 500 / e->map_size_y;
}

void		draw_map(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	e->origin_y = 140;
	compute_medium_distance(e);
	while (++i < e->map_size_y)
	{
		j = -1;
		e->origin_x = 220;
		while (++j < e->map_size_x)
		{
			if (i - 1 && e->map_tab[i][j] && e->map_tab[i][j - 1])
				draw_line(e, e->origin_x + e->distance_x, e->origin_y);
			draw_line(e, e->origin_x + e->distance_x, e->origin_y + e->map_tab[i][j]); // trace la ligne en relief
			draw_line(e, e->origin_x + e->distance_x, e->origin_y); // trace de gauche a droite
			if (i + 1 < e->map_size_y)
				draw_line(e, e->origin_x, e->origin_y + e->distance_y); // trace de haut en bas
			e->origin_x = e->origin_x + e->distance_x;
		}
		if (i + 1 < e->map_size_y)
			draw_line(e, e->origin_x, e->origin_y + e->distance_y); // trace de haut en bas
		e->origin_y = e->origin_y + e->distance_y;
	}
	e->origin_x = -1;
	e->origin_y = -1;
}

int			key_hook(int key, t_env *e)
{
	if (key == 53 || key == 8)
	{
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		free_env(e, NULL, 1);
	}
	if (key == 45)
	{
		e->origin_x = -1;
		e->origin_y = -1;
	}
	if (key == 36)
	{
		if (e->key_36)
		{
			e->origin_x = -1;
			e->origin_y = -1;
		}
		e->key_36 = 1;
		mlx_clear_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 10,
				e->mlx.color, "Press esc to exit\n");
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 25,
				e->mlx.color, "Press enter to clear\n");
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 40,
				e->mlx.color, "Press n to reset origin\n");
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 55,
				e->mlx.color, "Click to draw\n");
		draw_map(e);
	}
	return (0);
}

int			mouse_hook(int key, int x, int y, t_env *e)
{
	(void)key;
	if (e->origin_x != -1 && e->origin_y != -1)
		draw_line(e, x, y);
	if (e->key_36)
	{
		e->origin_x = (e->origin_x == -1) ? x : e->origin_x;
		e->origin_y = (e->origin_y == -1) ? y : e->origin_y;
	}
	return (0);
}

void		mlx_call(t_env *e)
{
	if (!(e->mlx.mlx_ptr = mlx_init()))
		free_env(e, NULL, 1);
	if (!(e->mlx.win_ptr = mlx_new_window(e->mlx.mlx_ptr, 1000, 750, "FDF")))
		free_env(e, NULL, 1);
	if (!(e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, 1000, 750)))
		free_env(e, NULL, 1);
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp,
			&e->mlx.s_l, &e->mlx.endian);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 375, 325,
			e->mlx.color, "PRESS ENTER TO START\n");
	mlx_key_hook(e->mlx.win_ptr, key_hook, e);
	mlx_mouse_hook(e->mlx.win_ptr, mouse_hook, e);
	mlx_loop(e->mlx.mlx_ptr);
}
