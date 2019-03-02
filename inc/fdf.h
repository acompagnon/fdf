/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:58:19 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/02 18:12:35 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>

/* ************************************************************************** */
# include <stdio.h>
/* ************************************************************************** */

typedef struct		s_map
{
	char			*line;
	int				id;
	struct s_map	*next;
}					t_map;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				endian;
	int				bpp;
	int				s_l;
	int				color;
}					t_mlx;

typedef struct		s_env
{
	struct s_map	*map;
	struct s_mlx	mlx;
	int				**map_tab;
	int				map_size_y;
	int				map_size_x;
}					t_env;

//MLX.C => 3
void				drawing_map(t_env *e);
int					key_hook(int key, t_env *e);
void				mlx_call(t_env *e);

//INIT.C => 1
void				init(t_env *e);

//FREE.C => 2
void				free_tab(t_env *e);
void				free_env(t_env *e, void *to_free, int to_exit);

//PRINT.C => 2
void				print_map(t_env *e);
void				print_tab(t_env *e);

//SORT_INPUT.C => 6
int					check_number(t_env *e, char *line);
int					malloc_tab(t_env *e);
void				fill_tab(t_env *e);
int					check_line(char *line);
int					save_line(t_env *e, char *line);
void				sort_input(t_env *e);

#endif
