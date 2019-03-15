/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:58:19 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/15 18:43:36 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# define PINK 0xFC0FC0
# define GREEN 0x009905
# define BLUE 0x3399ff
# define RED 0xFF0000
# define BLACK 0x000000
# define YELLOW 0xFFD300
# define WHITE 0xFFFFFF
# define WIN_X 1500
# define WIN_Y 1125

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
	int				medium_alt;
	int				altitude;
	double			zoom;
	int				zoom_x;
	int				zoom_y;
	int				move_x;
	int				move_y;
	int				center_x;
	int				center_y;
}					t_camera;

typedef struct		s_key
{
	int				left_click;
	int				left_click_x;
	int				left_click_y;
	int				iso;
	int				enter;
	int				mouse_released;
}					t_key;

typedef struct		s_env
{
	struct s_map	*map;
	struct s_mlx	mlx;
	struct s_camera	camera;
	struct s_key	key;
	int				**map_tab;
	int				menu_mode;
	double			map_size_y;
	double			map_size_x;
	double			dx;
	double			dy;
}					t_env;

//CLEAN.C => 4
void				move_image_to(t_env *e, int x, int y);
void				restart(t_env *e);
void				erase_zone(t_env *e, int x, int y);
void				clean_window(t_env *e);

//MENU.C => 1
void				add_side_menu(t_env *e);
void				menu_window(t_env *e);

//HOOKS.C => 3
int					key_hook(int key, t_env *e);
int					mouse_hook(int key, int x, int y, t_env *e);
int					motion_hook(int x, int y, t_env *e);
int					release_hook(int key, int x, int y, t_env *e);
int					holding_key(int key, t_env *e);

//DRAW.C => 5
void				put_pixel(t_env *e, int x, int y, int color);
void				draw_before(t_env *e, t_dot dot1, t_dot dot2, int color);
void				draw_after(t_env *e, t_dot dot1, t_dot dot2, int color);
void				draw_line(t_env *e, t_dot dot1, t_dot dot2, int color);
void				draw_map(t_env *e);

//CAMERA.C => 4
void				camera_moves(t_env *e, int *x, int *y);
void				take_best_alt(t_env *e, int *count1, int *count2, int alt_tmp);
void				find_medium_altitude(t_env *e);
void				find_zoom(t_env *e);

//INIT.C => 4
void				init_alt_var(int *i, int *count1, int *count2, int *alt_tmp);
t_dot				new_line(int y, int x);
t_dot				new_dot(t_env *e, int y, int x);
void				init(t_env *e);

//MALLOC_FREE.C => 3
int					malloc_tab(t_env *e);
void				free_tab(t_env *e);
void				free_env(t_env *e, void *to_free, int to_exit);

//SORT_INPUT.C => 5
int					check_number(t_env *e, char *line);
void				fill_tab(t_env *e, t_map *ptr);
double				check_line(char *line);
int					save_line(t_env *e, char *line);
void				sort_input(t_env *e);

#endif
