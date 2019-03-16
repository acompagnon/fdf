/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:18:37 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/16 17:34:46 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotate_x(t_env *e, int *y, int *z)
{
	int		tmp_y;
	int		tmp_z;

	tmp_y = *y;
	tmp_z = *z;
	if (e->rot_x)
	{
		*y = tmp_y * cos(e->rot_x) - sin(e->rot_x);
		*z = -tmp_y * sin(e->rot_x) + tmp_z * cos(e->rot_x);
	}
}

void		rotate_y(t_env *e, int *x, int *z)
{
	int		tmp_x;
	int		tmp_z;

	tmp_x = *x;
	tmp_z = *z;
	if (e->rot_y)
	{
		*x = tmp_x * cos(e->rot_y) + tmp_z * sin(e->rot_y);
		*z = -tmp_x * sin(e->rot_y) + tmp_z * cos(e->rot_y);
	}
}

void		rotate_z(t_env *e, int *x, int *y)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	if (e->rot_z)
	{
		*x = tmp_x * cos(e->rot_z) - tmp_y * sin(e->rot_z);
		*y = tmp_x * sin(e->rot_z) + tmp_y * cos(e->rot_z);
	}
}
