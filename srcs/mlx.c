/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:33:02 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/02 18:15:22 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			drawing_map(t_env *e)
{
	int		y;
	int		x;
	int		i;
	int		j;

	y = 375;
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 10, e->mlx.color, "ESC TO EXIT\n");

	while (++y - 375 < e->map_size_y)
	{
		x = 325;
		while (++x - 325 < e->map_size_x)
		{
			if (e->map_tab[y - 375][x - 325])
			{
				printf("e->map_tab[y - 375][x - 325] = %d\n", e->map_tab[y - 375][x - 325]);
				i = -1;
				while (++i < 10)
				{
					j = -1;
					while (++j < 10)
						mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, y + i, x + j, e->mlx.color);
				}
			}
		}
	}
}

int				key_hook(int key, t_env *e)
{
	if (key == 53 || key == 8)
	{
		mlx_destroy_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		free_env(e, NULL, 1);
	}
	if (key == 36)
	{
		mlx_clear_window(e->mlx.mlx_ptr, e->mlx.win_ptr);
		drawing_map(e);
	}
	return (0);
}

void			mlx_call(t_env *e)
{
	if (!(e->mlx.mlx_ptr = mlx_init()))
		free_env(e, NULL, 1);
	if (!(e->mlx.win_ptr = mlx_new_window(e->mlx.mlx_ptr, 1000, 750, "FDF")))
		free_env(e, NULL, 1);
	if (!(e->mlx.img_ptr = mlx_new_image(e->mlx.mlx_ptr, 1000, 750)))
		free_env(e, NULL, 1);
	e->mlx.data = mlx_get_data_addr(e->mlx.img_ptr, &e->mlx.bpp, &e->mlx.s_l, &e->mlx.endian);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 375, 325, e->mlx.color, "PRESS ENTER TO START\n");
	mlx_key_hook(e->mlx.win_ptr, key_hook, e);
	mlx_loop(e->mlx.mlx_ptr);
}
