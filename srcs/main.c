/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:57:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/12 19:14:48 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(void)
{
	t_env e;

	init(&e);
	sort_input(&e);
	if (!(e.mlx.mlx_ptr = mlx_init()))
		free_env(&e, NULL, 1);
	if (!(e.mlx.win_ptr = mlx_new_window(e.mlx.mlx_ptr, 1000, 750, "FDF")))
		free_env(&e, NULL, 1);
	if (!(e.mlx.img_ptr = mlx_new_image(e.mlx.mlx_ptr, 1000, 750)))
		free_env(&e, NULL, 1);
	e.mlx.data = mlx_get_data_addr(e.mlx.img_ptr, &e.mlx.bpp,
			&e.mlx.s_l, &e.mlx.endian);
	mlx_string_put(e.mlx.mlx_ptr, e.mlx.win_ptr, 395, 335,
			WHITE, "PRESS ENTER TO START\n");
	mlx_key_hook(e.mlx.win_ptr, key_hook, &e);
	mlx_hook(e.mlx.win_ptr, 2, 1L << 0, holding_key, &e);
	mlx_hook(e.mlx.win_ptr, 5, 1L << 3, test_hook, &e);
	mlx_hook(e.mlx.win_ptr, 6, 1L << 6, motion_hook, &e);
	mlx_mouse_hook(e.mlx.win_ptr, mouse_hook, &e);
	mlx_loop(e.mlx.mlx_ptr);
	free_env(&e, NULL, 0);
	return (0);
}
