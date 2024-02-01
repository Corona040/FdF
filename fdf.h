/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:50:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/01 17:33:27 by ecorona-         ###   ########.fr       */
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

/* ************************************************************************** */
// linalg.c
t_vector	*v_assign(t_vector *u, t_vector v, int inplace);
float_t	distance(t_vector *u, t_vector *v);
float_t	dot_product(t_vector *u, t_vector *v);
t_vector	*scalar_product(float_t a, t_vector *u, int inplace);
t_vector	*vector_product(t_vector *u, t_vector *v);
float_t	v_module(t_vector *u);
t_vector	*v_proj(t_vector *a, t_vector *b, int inplace);
t_vector	*v_rotate(t_vector *u, float_t a, int axis, int inplace);
t_vector	*v_planeproj(t_vector *u, int axis, int inplace);

#endif
