/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/08 17:05:42 by acompagn         ###   ########.fr       */
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
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
//	e->mlx.color = 0x009905;
	e->mlx.color = 0x3399ff;
}
