/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:58:49 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 15:00:47 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_side_menu(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 10, WHITE,
			"Press o to see options\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 270, WIN_Y - 60, WHITE,
			"p -> parallel projection\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 270, WIN_Y - 45, WHITE,
			"i -> iso projection\n");
}

void		menu_window(t_env *e)
{
	clean_window(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
			e->mlx.img_ptr, 0, 0);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 60,
			WHITE, "ESC         -> exit window\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 45,
			WHITE, "ENTER       -> reset\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 30,
			WHITE, "RIGHT CLICK -> erase mode\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 15,
			WHITE, "r           -> go back to map\n");

}
