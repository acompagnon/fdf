/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:03:45 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 15:16:40 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				check_number(t_env *e, char *line)
{
	int		i;
	int		nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = (line[i] == '-') ? -1 : 1;
	(line[i] == '-') ? i++ : 1;
	while (line[i] && line[i] != ' ')
	{
		if ((line[i] < '0' && line[i] > '9')
				|| nb * 10 + (line[i] - 48) > 2147483647)
			free_env(e, NULL, 1);
		else
			nb = nb * 10 + (line[i] - 48);
		i++;
	}
	return (nb * sign);
}

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

void			fill_tab(t_env *e)
{
	t_map	*ptr;
	int		i;
	int		y;
	int		x;

	ptr = e->map;
	y = 0;
	while (ptr)
	{
		i = 0;
		x = 0;
		while (ptr->line[i])
		{
			if (x == e->map_size_x || y == e->map_size_y)
				break ;
			e->map_tab[y][x++] = check_number(e, &ptr->line[i]);
			(e->map_tab[y][x - 1] < 0) ? i++ : 1;
			while (ptr->line[i] && ptr->line[i] >= '0' && ptr->line[i] <= '9')
				i++;
			(ptr->line[i] && ptr->line[i] != ' ') ? free_env(e, NULL, 1) : 1;
			while (ptr->line[i] && ptr->line[i] == ' ')
				i++;
		}
		ptr = ptr->next;
		y++;
	}
}

double			check_line(char *line)
{
	int		i;
	double	nb;

	i = 0;
	nb = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '-'
				&& (line[i] < '0' || line[i] > '9'))
			return (0);
		(line[i] == ' ') ? i++ : 1;
		if (line[i] && (line[i] == '-' || (line[i] >= '0' && line[i] <= '9')))
			nb++;
		while (line[i] && (line[i] == '-'
				|| (line[i] >= '0' && line[i] <= '9')))
			i++;
	}
	return (nb);
}

int				save_line(t_env *e, char *line)
{
	t_map	*new;
	t_map	*ptr;

	ptr = e->map;
	if (!(new = (t_map *)ft_memalloc(sizeof(t_map))))
		return (0);
	if (!(new->line = ft_strdup(line)))
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (!e->map)
		e->map = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		new->id = ptr->id + 1;
		ptr->next = new;
	}
	return (1);
}

void			find_medium_altitude(t_env *e)
{
	int		i;
	int		j;
	int		count1;
	int		count2;
	int		alt_tmp;

	i = -1;
	count1 = 0;
	count2 = 0;
	alt_tmp = 0;
	while (++i < e->map_size_y)
	{
		j = -1;
		while (++j < e->map_size_x)
		{
			if (count2 > count1)
			{
				e->camera.medium_alt = alt_tmp;
				count1 = count2;
				count2 = 0;
			}
			if (!e->camera.medium_alt || e->map_tab[i][j] == e->camera.medium_alt)
			{
				e->camera.medium_alt = e->map_tab[i][j];
				count1++;
			}
			else if (!alt_tmp || e->map_tab[i][j] == alt_tmp)
				count2++;
		}
	}
}

void			find_zoom(t_env *e)
{
	e->camera.zoom = (WIN_X / 10 / e->map_size_y) * 3.5;
}

void			sort_input(t_env *e)
{
	char	*line;
	double	len;

	while (get_next_line(0, &line) > 0)
	{
		if ((len = check_line(line)))
		{
			if (len <= 0 || (e->map_size_x && len != e->map_size_x)
					|| !(save_line(e, line)))
				free_env(e, line, 1);
			e->map_size_x = len;
			e->map_size_y++;
		}
		else
			free_env(e, line, 1);
		free(line);
	}
	(!(malloc_tab(e))) ? free_env(e, NULL, 1) : 1;
	fill_tab(e);
	find_medium_altitude(e);
	find_zoom(e);
}
