/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:33:02 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 15:15:34 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
void		rotate_x(t_env *e, t_dot *dot)
{
	
}

void		rotate_y(t_env *e, t_dot *dot)
{
	
}

void		rotate_z(t_env *e, t_dot *dot)
{
	
}
*/
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

	dot.x = x * e->zoom + 400;
	dot.y = y * e->zoom - 50;
	dot.z = e->map_tab[y][x];
	return (dot);
}

void		iso(int *x, int *y, int z)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(0.523599);
	*y = -z + (tmp_x + tmp_y) * sin(0.523599);
}

t_dot		projection(t_dot dot)
{
	iso(&dot.x, &dot.y, dot.z);
	return (dot);
}

void		draw_map(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	while (++i < e->map_size_y)
	{
		j = -1;
		while (++j < e->map_size_x)
		{
			if (i + 1 < e->map_size_y)
				draw_line(e, projection(new_dot(e, i, j)), projection(new_dot(e, i + 1, j)),
						e->color.blue);
			if (j + 1 < e->map_size_x)
				draw_line(e, projection(new_dot(e, i, j)), projection(new_dot(e, i, j + 1)),
						e->color.yellow);
		}
	}
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
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 395, 335,
			e->color.white, "PRESS ENTER TO START\n");
	mlx_key_hook(e->mlx.win_ptr, key_hook, e);
	mlx_hook(e->mlx.win_ptr, 5, 1L<<3, test_hook, e);
	mlx_hook(e->mlx.win_ptr, 6, 1L<<6, motion_hook, e);
	mlx_mouse_hook(e->mlx.win_ptr, mouse_hook, e);
	mlx_loop(e->mlx.mlx_ptr);
}
