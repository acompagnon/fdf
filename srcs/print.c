/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:47:22 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/02 15:02:48 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				print_map(t_env *e)
{
	t_map	*ptr;

	ptr = e->map;
	while (ptr)
	{
		printf("y = %d  && line = %s\n", ptr->id, ptr->line);
		ptr = ptr->next;
	}
}

void				print_tab(t_env *e)
{
	int		y;
	int		x;

	y = -1;
	while (++y < e->map_size_y)
	{
		x = -1;
		while (++x < e->map_size_x)
			printf("%2d ", e->map_tab[y][x]);
		printf("\n");
	}
}
