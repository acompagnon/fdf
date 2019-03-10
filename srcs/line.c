/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:02:31 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/10 17:13:25 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			abs_value(int nb)
{
	return ((nb < 0) ? -nb : nb);
}

void		draw_before(t_env *e, int x, int y, int color)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dx / 2;
	tmp_x = e->origin_x;
	tmp_y = e->origin_y;
	while (i <= e->dx)
	{
		(x - e->origin_x > 0) ? tmp_x++ : tmp_x--;
		cumul += e->dy;
		if (cumul >= e->dx)
		{
			cumul -= e->dx;
			(y - e->origin_y > 0) ? tmp_y++ : tmp_y--;
		}
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
				tmp_y, color);
		i++;
	}
}

void		draw_after(t_env *e, int x, int y, int color)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dy / 2;
	tmp_x = e->origin_x;
	tmp_y = e->origin_y;
	while (i <= e->dy)
	{
		(y - e->origin_y > 0) ? tmp_y++ : tmp_y--;
		cumul += e->dx;
		if (cumul >= e->dy)
		{
			cumul -= e->dy;
			(x - e->origin_x > 0) ? tmp_x++ : tmp_x--;
		}
		mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
				tmp_y, color);
		i++;
	}
}

void		draw_line(t_env *e, int x, int y, int color)
{
	e->dx = abs_value(x - e->origin_x);
	e->dy = abs_value(y - e->origin_y);
//	if (color == e->color.red)
//		printf("distance_x = %d\ndistance_y = %d\n\n", e->dx, e->dy);
	mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, e->origin_x,
			e->origin_y, color);
	if (e->dx > e->dy)
		draw_before(e, x, y, color);
	else
		draw_after(e, x, y, color);
}
