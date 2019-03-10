/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/10 17:29:03 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			init(t_env *e)
{
	e->map = NULL;
	e->map_tab = NULL;
	e->map_size_y = 0;
	e->map_size_x = 0;
	e->distance_x = 0;
	e->distance_y = 0;
	e->key_36 = 0;
	e->key_125 = 0;
	e->key_126 = 0;
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
	e->color.green = 0x009905;
	e->color.blue = 0x3399ff;
	e->color.red = 0xFF0000;
	e->color.black = 0x000000;
	e->color.pink = 0xFC0FC0;
	e->color.yellow = 0xFFD300;
	e->color.white = 0xFFFFFF;
	e->mouse_released = 0;
}
