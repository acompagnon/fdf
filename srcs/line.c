/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 15:02:31 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 17:39:36 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			abs_value(int nb)
{
	return ((nb < 0) ? -nb : nb);
}

void		put_pixel(t_env *e, int x, int y, int color)
{
	int		i;

	if (x > 0 && y > 0 && y < 750 && x < 1000)
	{
		i = (x * e->mlx.bpp / 8) + (y * e->mlx.s_l);
		e->mlx.data[i++] = color >> 16;
		e->mlx.data[i++] = color >> 8;
		e->mlx.data[i] = color;
	}
}

void		draw_before(t_env *e, t_dot dot1, t_dot dot2, int color)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dx / 2;
	tmp_x = dot2.x;
	tmp_y = dot2.y;
	while (i <= e->dx)
	{
		(dot1.x - dot2.x > 0) ? tmp_x++ : tmp_x--;
		cumul += e->dy;
		if (cumul >= e->dx)
		{
			cumul -= e->dx;
			(dot1.y - dot2.y > 0) ? tmp_y++ : tmp_y--;
		}
		put_pixel(e, tmp_x, tmp_y, color);
		i++;
	}
}

void		draw_after(t_env *e, t_dot dot1, t_dot dot2, int color)
{
	int		i;
	int		cumul;
	int		tmp_x;
	int		tmp_y;

	i = 1;
	cumul = e->dy / 2;
	tmp_x = dot2.x;
	tmp_y = dot2.y;
	while (i <= e->dy)
	{
		(dot1.y - dot2.y > 0) ? tmp_y++ : tmp_y--;
		cumul += e->dx;
		if (cumul >= e->dy)
		{
			cumul -= e->dy;
			(dot1.x - dot2.x > 0) ? tmp_x++ : tmp_x--;
		}
		put_pixel(e, tmp_x, tmp_y, color);
		i++;
	}
}

void		draw_line(t_env *e, t_dot dot1, t_dot dot2, int color)
{
	e->dx = abs_value(dot1.x - dot2.x);
	e->dy = abs_value(dot1.y - dot2.y);
	put_pixel(e, dot2.x, dot2.y, color);
	if (e->dx > e->dy)
		draw_before(e, dot1, dot2, color);
	else
		draw_after(e, dot1, dot2, color);
}
