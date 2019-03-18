/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:12:45 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/18 11:55:17 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		camera_moves(t_env *e, int *x, int *y)
{
	if (e->camera.zoom_x && e->camera.zoom_y)
	{
		*x -= e->camera.zoom_x / 2;
		*y -= e->camera.zoom_y / 2;
	}
	if (e->camera.move_x && e->camera.move_y)
	{
		*x += e->camera.move_x - e->key.left_click_x;
		*y += e->camera.move_y - e->key.left_click_y;
	}
}

static void	take_best_alt(t_env *e, int *count1, int *count2, int alt_tmp)
{
	e->camera.medium_alt = alt_tmp;
	*count1 = *count2;
	*count2 = 0;
}

void		find_medium_altitude(t_env *e)
{
	int		i;
	int		j;
	int		count1;
	int		count2;
	int		alt_tmp;

	init_alt_var(&i, &count1, &count2, &alt_tmp);
	while (++i < e->map_size_y)
	{
		j = -1;
		while (++j < e->map_size_x)
		{
			if (count2 < count1)
				take_best_alt(e, &count1, &count2, alt_tmp);
			if (!e->camera.medium_alt
					|| e->map_tab[i][j] == e->camera.medium_alt)
			{
				e->camera.medium_alt = e->map_tab[i][j];
				count1++;
			}
			else if (!alt_tmp || e->map_tab[i][j] == alt_tmp)
				count2++;
		}
	}
}

void		find_zoom(t_env *e)
{
	e->camera.zoom = 1;
	while (e->camera.zoom * e->map_size_y < WIN_Y / 2
			&& e->camera.zoom * e->map_size_x < WIN_X / 1.5)
		e->camera.zoom++;
}
