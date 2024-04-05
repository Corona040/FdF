/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:00:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 08:39:38 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

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
			return (NULL);
	}
	k = v_module(b);
	k = v_dot_product(a, b) / (k * k);
	aux = v_scalar_product(k, b, 0);
	if (!aux)
		return (NULL);
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
			return (NULL);
	}
	proj = v_proj(u, &axis, 0);
	if (!proj)
		return (NULL);
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
	if (!ax)
		return (NULL);
	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (NULL);
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

t_vector	*v_shift(t_vector *u, t_vector axis, float_t val, int inplace)
{
	t_vector	*result;
	t_vector	*ax;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (NULL);
	}
	ax = v_norm(&axis, 0);
	if (!ax)
		return (NULL);
	v_scalar_product(val, ax, 1);
	result = v_sum(u, ax, inplace);
	free(ax);
	return (result);
}
