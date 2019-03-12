/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:42:15 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/12 19:19:43 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotate_x(t_env *e, int *y, int *z)
{
	double	tmp_y;
	double	tmp_z;

	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(e->camera.rot_x) + tmp_z * sin(e->camera.rot_x);
	*z = -tmp_y * sin(e->camera.rot_x) + tmp_z * cos(e->camera.rot_x);
}

void		rotate_y(t_env *e, int *x, int *z)
{
	double	tmp_x;
	double	tmp_z;

	tmp_x = *x;
	tmp_z = *z;
	*x = tmp_x * cos(e->camera.rot_y) + tmp_z * sin(e->camera.rot_y);
	*z = -tmp_x * sin(e->camera.rot_y) + tmp_z * cos(e->camera.rot_y);
}

void		rotate_z(t_env *e, int *x, int *y)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(e->camera.rot_z) - tmp_y * sin(e->camera.rot_z);
	*y = tmp_x * sin(e->camera.rot_z) + tmp_y * cos(e->camera.rot_z);
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

t_dot		projection(t_env *e, t_dot dot)
{
	rotate_x(e, &dot.y, &dot.z);
	rotate_y(e, &dot.x, &dot.z);
	rotate_z(e, &dot.x, &dot.y);
	if (e->key_34)
		iso(&dot.x, &dot.y, dot.z);
	return (dot);
}
