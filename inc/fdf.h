/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:58:19 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/11 17:39:38 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>

/* ************************************************************************** */
# include <stdio.h>
/* ************************************************************************** */
# define PINK 0xFC0FC0
# define GREEN 0x009905
# define BLUE 0x3399ff
# define RED 0xFF0000
# define BLACK 0x000000
# define YELLOW 0xFFD300
# define WHITE 0xFFFFFF


typedef struct		s_map
{
	char			*line;
	int				id;
	struct s_map	*next;
}					t_map;

typedef struct		s_dot
{
	int				x;
	int				y;
	int				z;
}					t_dot;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				endian;
	int				bpp;
	int				s_l;
}					t_mlx;

typedef struct		s_camera
{
	int				zoom;
	int				altitude;
	double			rot_x;
	double			rot_y;
	double			rot_z;
}					t_camera;

typedef struct		s_env
{
	struct s_map	*map;
	struct s_mlx	mlx;
	struct s_camera	camera;
	int				**map_tab;
	int				map_size_y;
	int				map_size_x;
	int				key_36;
	int				dx;
	int				dy;
	double			origin_x;
	double			origin_y;
	int				mouse_released;
}					t_env;

//HOOKS.C => 3
void				erase_zone(t_env *e, int x, int y);
void				clean_window(t_env *e);
void				menu_window(t_env *e);
int					key_hook(int key, t_env *e);
int					mouse_hook(int key, int x, int y, t_env *e);
int					motion_hook(int x, int y, t_env *e);
int					test_hook(int key, int x, int y, t_env *e);
void				erase_zone(t_env *e, int x, int y);

//LINE.C => 4
int					abs_value(int nb);
void				put_pixel(t_env *e, int x, int y, int color);
void				draw_before(t_env *e, t_dot dot1, t_dot dot2, int color);
void				draw_after(t_env *e, t_dot dot1, t_dot dot2, int color);
void				draw_line(t_env *e, t_dot dot1, t_dot dot2, int color);

//MLX.C => 4
t_dot				new_line(int y, int x);
t_dot				new_dot(t_env *e, int y, int x);
void				iso(int *x, int *y, int z);
void				draw_map(t_env *e);
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
