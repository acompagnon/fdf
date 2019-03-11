/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:58:49 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 19:06:47 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		menu_window(t_env *e)
{
	clean_window(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
			e->mlx.img_ptr, 0, 0);
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
