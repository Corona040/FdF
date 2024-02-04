/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:07:45 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/03 21:19:50 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAAG_H
# define LAAG_H

# include <math.h>
# include "libft.h"

typedef struct s_vector
{
	float_t	x;
	float_t	y;
	float_t	z;
}	t_vector;

typedef struct s_quaternion
{
	float_t	w;
	float_t	i;
	float_t	j;
	float_t	k;
}	t_quaternion;

/* ************************************************************************** */
// laag_basic.c
t_vector		*v_assign(t_vector *u, t_vector v, int inplace);
t_vector		*v_sum(t_vector *u, t_vector *v, int inplace);
float_t			v_module(t_vector *u);
float_t			v_distance(t_vector *u, t_vector *v);
t_vector		*v_norm(t_vector *u, int inplace);
/* ************************************************************************** */
// laag_product.c
t_vector		*v_scalar_product(float_t a, t_vector *u, int inplace);
float_t			v_dot_product(t_vector *u, t_vector *v);
t_vector		*v_vector_product(t_vector *u, t_vector *v);
/* ************************************************************************** */
// laag_operations.c
t_vector		*v_proj(t_vector *a, t_vector *b, int inplace);
t_vector		*v_planeproj(t_vector *u, t_vector axis, int inplace);
t_vector		*v_rotate(t_vector *u, t_vector axis, float_t a, int inplace);
t_vector		*v_shift(t_vector *u, t_vector axis, float_t val, int inplace);
/* ************************************************************************** */
// laag_quaternion.c
float_t			q_modules(t_quaternion *q);
t_quaternion	*q_conjugate(t_quaternion *q, int inplace);
t_quaternion	*q_scalar_product(float_t a, t_quaternion *q, int inplace);
t_quaternion	*q_inverse(t_quaternion *q, int inplace);
t_quaternion	*q_product(t_quaternion *q, t_quaternion *p, int inplace);

#endif
