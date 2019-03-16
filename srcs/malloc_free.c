/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:43:56 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/16 13:43:30 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				malloc_tab(t_env *e)
{
	int		i;

	i = -1;
	if (!(e->map_tab = (int **)ft_memalloc(sizeof(int *) * e->map_size_y)))
		return (0);
	while (++i < e->map_size_y)
		if (!(e->map_tab[i] = (int *)ft_memalloc(sizeof(int) * e->map_size_x)))
		{
			while (i--)
				free(e->map_tab[i]);
			free(e->map_tab);
			return (0);
		}
	return (1);
}

static void		free_tab(t_env *e)
{
	int		i;

	i = -1;
	while (++i < e->map_size_y)
		free(e->map_tab[i]);
	free(e->map_tab);
}

void			free_env(t_env *e, void *to_free, int to_exit)
{
	t_map	*tmp;

	while (e->map)
	{
		tmp = e->map;
		e->map = e->map->next;
		free(tmp);
	}
	(e->map_tab) ? free_tab(e) : 1;
	to_free ? free(to_free) : 1;
	to_exit ? exit(1) : 1;
}
