/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:00:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/02 02:29:20 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*v_sum(t_vector *u, t_vector *v, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("sum v fail\n");
	}
	result->x = u->x + v->x;
	result->y = u->y + v->y;
	result->z = u->z + v->z;
	return (result);
}

t_vector	*v_assign(t_vector *u, t_vector v, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("v_scalar_product fail\n");
	}
	result->x = v.x;
	result->y = v.y;
	result->z = v.z;
	return (result);
}

float_t	v_distance(t_vector *u, t_vector *v)
{
	t_vector	diff;

	diff.x = u->x - v->x;
	diff.y = u->y - v->y;
	diff.z = u->z - v->z;
	return (v_module(&diff));
}

float_t	v_dot_product(t_vector *u, t_vector *v)
{
	float_t	result;

	result = 0;
	result += u->x * v->x;
	result += u->y * v->y;
	result += u->z * v->z;
	return (result);
}

t_vector	*v_norm(t_vector *u, int inplace)
{
	t_vector	*result;
	float_t		module;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("norm fail\n");
	}
	module = v_module(u);
	result->x = u->x / module;
	result->y = u->y / module;
	result->z = u->z / module;
	return (result);
}

t_vector	*v_scalar_product(float_t a, t_vector *u, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("v_scalar_product fail\n");
	}
	result->x = a * u->x;
	result->y = a * u->y;
	result->z = a * u->z;
	return (result);
}

t_vector	*v_vector_product(t_vector *u, t_vector *v)
{
	t_vector	*result;

	result = ft_calloc(1, sizeof(*result));
	if (!result)
		ft_printf("v_scalar_product fail\n");
	result->x = (u->y * v->z) - (u->z * v->y);
	result->y = (u->z * v->x) - (u->x * v->z);
	result->z = (u->x * v->y) - (u->y * v->x);
	return (result);
}

float_t	v_module(t_vector *u)
{
	return (sqrtf(fabsf(v_dot_product(u, u))));
}

t_vector	*v_proj(t_vector *a, t_vector *b, int inplace)
{
	t_vector	*result;
	t_vector	*aux;
	float_t		k;

	if (inplace)
		result = a;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("v_scalar_product fail\n");
	}
	k = v_module(b);
	k = v_dot_product(a, b) / (k * k);
	aux = v_scalar_product(k, b, 0);
	v_assign(result, *aux, 1);
	free(aux);
	return (result);
}

t_vector	*v_planeproj(t_vector *u, t_vector axis, int inplace)
{
	t_vector	*result;
	t_vector	*proj;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("v_scalar_product fail\n");
	}
	proj = v_proj(u, &axis, 0);
	v_assign(result, *u, 1);
	result->x -= proj->x;
	result->y -= proj->y;
	result->z -= proj->z;
	free(proj);
	return (result);
}

t_vector	*v_rotate(t_vector *u, t_vector axis, float_t a, int inplace)
{
	t_vector		*result;
	t_quaternion	uq;
	t_quaternion	q;
	t_quaternion	*iq;
	t_vector		*ax;

	ax = v_norm(&axis, 0);
	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("rotate fail");
	}
	uq = (t_quaternion){0, u->x, u->y, u->z};
	q = (t_quaternion){cosf(a / 2), sinf(a / 2) * ax->x, \
		sinf(a / 2) * ax->y, sinf(a / 2) * ax->z};
	iq = q_inverse(&q, 0);
	q_product(&q, &uq, 1);
	q_product(&q, iq, 1);
	free(iq);
	free(ax);
	v_assign(result, (t_vector){q.i, q.j, q.k}, 1);
	return (result);
}

t_vector	*v_translate(t_vector *u, t_vector axis, float_t val, int inplace)
{
	t_vector	*result;
	t_vector	*ax;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("rotate fail");
	}
	ax = v_norm(&axis, 0);
	v_scalar_product(val, ax, 1);
	result = v_sum(u, ax, inplace);
	free(ax);
	return (result);
}
