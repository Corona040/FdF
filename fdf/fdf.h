/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:50:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/03 18:09:36 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include <math.h>
# include "X11/X.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"

# define XK_Escape 0xff1b

struct window
{
	void	*mlx_ptr;
	void	*win_ptr;
};

typedef struct s_vector
{
	float_t x;
	float_t y;
	float_t z;
}	t_vector;

typedef struct s_quaternion
{
	float_t	w;
	float_t	i;
	float_t	j;
	float_t	k;
}	t_quaternion;

typedef struct s_image_conf
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
}	t_img;

typedef struct s_object
{
	int				size;
	t_vector		origin;
	t_vector		speed;
	t_vector		**obj;
	struct window	*window;
}	t_object;

/* ************************************************************************** */
// linalg.c
t_vector	*v_sum(t_vector *u, t_vector *v, int inplace);
t_vector	*v_assign(t_vector *u, t_vector v, int inplace);
float_t		v_distance(t_vector *u, t_vector *v);
float_t		v_dot_product(t_vector *u, t_vector *v);
t_vector	*v_norm(t_vector *u, int inplace);
t_vector	*v_scalar_product(float_t a, t_vector *u, int inplace);
t_vector	*v_vector_product(t_vector *u, t_vector *v);
float_t		v_module(t_vector *u);
t_vector	*v_proj(t_vector *a, t_vector *b, int inplace);
t_vector	*v_planeproj(t_vector *u, t_vector axis, int inplace);
t_vector	*v_rotate(t_vector *u, t_vector axis, float_t a, int inplace);
t_vector	*v_translate(t_vector *u, t_vector axis, float_t val, int inplace);
/* ************************************************************************** */
// quaternion.c
float_t			q_modules(t_quaternion *q);
t_quaternion	*q_conjugate(t_quaternion *q, int inplace);
t_quaternion	*q_scalar_product(float_t a, t_quaternion *q, int inplace);
t_quaternion	*q_inverse(t_quaternion *q, int inplace);
t_quaternion	*q_product(t_quaternion *q, t_quaternion *p, int inplace);
/* ************************************************************************** */
// draw.c
void	draw_point(t_vector *p, struct window *window);
void	connect_vertices(t_vector *vertice1, t_vector *vertice2, struct window *window);

#endif
