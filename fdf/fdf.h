/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:50:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 04:00:55 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include <math.h>
# include "X11/X.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "laag.h"

# define XK_Escape 0xff1b

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
}	t_scene;

/* ************************************************************************** */
// draw.c
void		draw_point(t_vector *p, t_img *img);
void		connect_vertices(t_vector *v1, t_vector *v2, t_img *img);
t_img		*create_img(void *mlx_ptr, int width, int height, t_img_conf *conf);
int			img_pixel_put(t_img *img, int x, int y, int color);
t_vector	**create_grid(int width, int height, int step);
void		scene_draw(t_scene *scene);

#endif
