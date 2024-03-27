/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:50:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/03/27 20:45:11 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include <math.h>
# include "X11/X.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "laag.h"

# define XK_Escape 0xff1b
# define XK_p 0x0070
# define WIN_X 1000
# define WIN_Y 1000
# define GRID_STEP 20
# define Z_FACTOR 5
# define IMG_X 1000
# define IMG_Y 1000
# define CAM_POS 500
# define FOV 100
# define ZOOM_FACTOR 25
# define MOVE_FACTOR	1
# define ROT_FACTOR .01
# define ZOOM 10

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
	t_vector	**grid;
	t_img		*img;
	t_win		*win;
}	t_obj;

typedef struct s_camera
{
	t_vector	origin;
	float_t		dist;
}	t_cam;

typedef struct s_scene
{
	t_obj		*obj;
	t_cam		*cam;
	t_vector	origin;
	int			perspective;
}	t_scene;

/* ************************************************************************** */
// draw.c
void		draw_point(t_vector *p, t_img *img);
int			get_color_from_warp(float_t z_warp);
void		connect_vertices(t_vector *v1, t_vector *v2, t_img *img);
t_vector	**create_grid(int width, int height, float_t step);
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
