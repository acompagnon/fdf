/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:03:08 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 17:39:32 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			init(t_env *e)
{
	e->map = NULL;
	e->map_tab = NULL;
	e->map_size_y = 0;
	e->map_size_x = 0;
	e->key_36 = 0;
	e->camera.zoom = 30;
	e->camera.altitude = 0;
	e->camera.rot_x = 0.00;
	e->camera.rot_y = 0.00;
	e->camera.rot_z = 0.00;
	e->origin_x = -1;
	e->origin_y = -1;
	e->mlx.bpp = 32;
	e->mlx.endian = 0;
	e->mlx.s_l = 800 * 4;
	e->mouse_released = 0;
}
