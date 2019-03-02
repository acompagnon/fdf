/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:59:31 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/02 15:20:07 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			free_tab(t_env *e)
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
