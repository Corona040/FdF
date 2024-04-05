/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:50:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 09:14:45 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "X11/X.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "laag.h"

# define XK_ESCAPE 0xff1b
# define XK_P 0x0070
# define XK_UP 0xff52
# define XK_DOWN 0xff54
# define WIN_X 1000
# define WIN_Y 1000
# define GRID_STEP 10
# define Z_FACTOR GRID_STEP/10
# define IMG_X 1000
# define IMG_Y 1000
# define CAM_POS 500
# define FOV CAM_POS/10
# define ZOOM_FACTOR 100
# define MOVE_FACTOR 1
# define ROT_FACTOR .01
# define ZOOM FOV/5

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_arc
{
	t_vector	*v1;
	t_vector	*v2;
	t_rgb		c1;
	t_rgb		c2;
}	t_arc;

typedef struct s_grid
{
	int			xy[2];
	t_vector	**v;
	t_rgb		**c;
}	t_grid;

typedef struct s_map
{
	int		x;
	int		y;
	char	***vals;
}	t_map;

typedef struct window
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_win;

typedef struct s_image_configuration
{
	int		bpp;
	int		len;
	int		end;
}	t_img_conf;

typedef struct s_image
{
	void		*img_ptr;
	char		*data;
	int			width;
	int			height;
	t_img_conf	conf;
	int			x;
	int			y;
}	t_img;

typedef struct s_object
{
	t_vector	origin;
	int			width;
	int			height;
	t_grid		*grid;
	t_img		*img;
	t_win		*win;
}	t_obj;

typedef struct s_camera
{
	t_vector	origin;
	float_t		dist;
	float_t		zoom_factor;
}	t_cam;

typedef struct s_scene
{
	t_obj		*obj;
	t_cam		*cam;
	t_vector	origin;
	int			perspective;
}	t_scene;

/* ************************************************************************** */
// free_.c
void		free_matrix(void **m, int n);
void		free_obj(t_obj *obj);
void		free_scene(t_scene *scene);
void		free_map(t_map *map);
/* ************************************************************************** */
// fdf.c
void		init_scene_from_map(t_scene *scene, t_map map);
void		isometric_ize(t_scene *scene);
void		parallel_ize(t_scene *scene);
void		hook_n_loop(t_scene *scene);
/* ************************************************************************** */
// read_map.c
t_map		read_map_file(char *path);
int			map_append(t_map *map, char **z_val);
t_grid		*get_grid_from_map(t_map map);
int			xatoi(char *hex);
t_rgb		itoc(int i);
int			ctoi(t_rgb rgb);
/* ************************************************************************** */
// draw.c
void		draw_point(t_vector *p, t_rgb color, t_img *img);
int			get_color_from_warp(float_t z_warp);
void		connect_vertices(t_arc arc, t_img *img);
t_vector	**create_gridv(int width, int height, float_t step);
t_rgb		**create_gridc(int width, int height);
t_rgb		get_gradient(t_rgb c1, t_rgb c2, float_t dist);
void		scene_draw(t_scene *scene);
void		obj_rotate(t_obj *obj, t_vector axis, float_t a);
void		obj_translate(t_obj *obj, t_vector axis, float_t val);
int			animate(void *param);
int			scene_rot(void *param);
int			scene_shift(void *param);
int			mouse_press_hook(int button, int x, int y, void *param);
int			mouse_release_hook(int button, int x, int y, void *param);
int			quit(void *param);
int			key_hook(int keycode, void *param);
/* ************************************************************************** */
// image.c
t_img		*create_img(void *mlx_ptr, int width, int height, t_img_conf *conf);
int			img_pixel_put(t_img *img, int x, int y, int color);

#endif
