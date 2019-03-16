/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:58:49 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/16 15:21:33 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_side_menu(t_env *e)
{
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10, 10, WHITE,
			"Press o to see options\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 270,
			WIN_Y - 60, WHITE, "p -> parallel projection\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 270,
			WIN_Y - 35, WHITE, "i -> iso projection\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10,
			WIN_Y - 35, WHITE, "Move image with left click\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 10,
			WIN_Y - 60, WHITE, "Erase with right click\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 280,
			10, WHITE, "up arrow   -> more altitude\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 280,
			25, WHITE, "down arrow -> less altitude\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X - 280,
			40, WHITE, "scroll     -> zoom in / out\n");
}

int			color(int color_place)
{
	if (color_place == 0)
		return (PINK);
	else if (color_place == 25)
		return (GREEN);
	else if (color_place == 50)
		return (BLUE);
	else if (color_place == 75)
		return (RED);
	else if (color_place == 100)
		return (YELLOW);
	else if (color_place == 125)
		return (WHITE);
	return (BLACK);
}

static void	add_color_choice(t_env *e, int code)
{
	int		x;
	int		y;
	int		tmp_x;
	int		tmp_y;
	int		color_place;

	color_place = 0;
	while (color_place <= 125)
	{
		x = WIN_X / 2.75 + 10 + color_place;
		y = WIN_Y / 2 - (code ? 75 : 125);
		tmp_y = y - 10;
		while (++tmp_y < y + 10)
		{
			tmp_x = x - 10;
			mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
					tmp_y, color(color_place));
			while (++tmp_x < x + 10)
				mlx_pixel_put(e->mlx.mlx_ptr, e->mlx.win_ptr, tmp_x,
						tmp_y, color(color_place));
		}
		color_place += 25;
	}
}

void		menu_window(t_env *e)
{
	clean_window(e);
	mlx_put_image_to_window(e->mlx.mlx_ptr, e->mlx.win_ptr,
			e->mlx.img_ptr, 0, 0);
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 60,
			WHITE, "ESC         -> exit window\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 45,
			WHITE, "ENTER       -> reset\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 30,
			WHITE, "RIGHT CLICK -> erase mode\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75, WIN_Y / 2 - 15,
			WHITE, "r           -> go back to map\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75,
			WIN_Y / 2 - 110, WHITE, "Click to choose color 2\n");
	mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, WIN_X / 2.75,
			WIN_Y / 2 - 160, WHITE, "Click to choose color 1\n");
	add_color_choice(e, 0);
	add_color_choice(e, 1);
}
