/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:59:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 16:07:01 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		put_pixel(t_env *e, int x, int y, int color)
{
	int		i;

	if (x > 0 && y > 0 && y < WIN_Y && x < WIN_X)
	{
		i = (x * e->mlx.bpp / 8) + (y * e->mlx.s_l);
		e->mlx.data[i++] = color & 0xff;
		e->mlx.data[i++] = color >> 8 & 0xff;
		e->mlx.data[i] = color >> 16 & 0xff;
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
	e->dx = abs_double(dot1.x - dot2.x);
	e->dy = abs_double(dot1.y - dot2.y);
	put_pixel(e, dot2.x, dot2.y, color);
	if (e->dx > e->dy)
		draw_before(e, dot1, dot2, color);
	else
		draw_after(e, dot1, dot2, color);
}

void		draw_map(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	clean_window(e);
	while (++i < e->map_size_y)
	{
		j = -1;
		while (++j < e->map_size_x)
		{
			if (i + 1 < e->map_size_y)
				draw_line(e, new_dot(e, i, j), new_dot(e, i + 1, j), BLUE);
			if (j + 1 < e->map_size_x)
				draw_line(e, new_dot(e, i, j), new_dot(e, i, j + 1), YELLOW);
		}
	}
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
			e->mlx.img_ptr, 0, 0);
	add_side_menu(e);
}
