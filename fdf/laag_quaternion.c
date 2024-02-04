/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_quaternion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:05:09 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/03 21:32:16 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

float_t	q_modules(t_quaternion *q)
{
	float_t	result;

	result = 0;
	result += q->w * q->w;
	result += q->i * q->i;
	result += q->j * q->j;
	result += q->k * q->k;
	return (result);
}

t_quaternion	*q_conjugate(t_quaternion *q, int inplace)
{
	t_quaternion	*result;

	if (inplace)
		result = q;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (0);
	}
	result->w = q->w;
	result->i = -(q->i);
	result->j = -(q->j);
	result->k = -(q->k);
	return (result);
}

t_quaternion	*q_scalar_product(float_t a, t_quaternion *q, int inplace)
{
	t_quaternion	*result;

	if (inplace)
		result = q;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (0);
	}
	result->w = a * q->w;
	result->i = a * q->i;
	result->j = a * q->j;
	result->k = a * q->k;
	return (result);
}

t_quaternion	*q_inverse(t_quaternion *q, int inplace)
{
	t_quaternion	*result;
	float_t			norm_sqr;

	if (inplace)
		result = q;
	norm_sqr = q_modules(q);
	result = q_conjugate(q, inplace);
	if (!result)
		return (0);
	result->w /= norm_sqr;
	result->i /= norm_sqr;
	result->j /= norm_sqr;
	result->k /= norm_sqr;
	return (result);
}

t_quaternion	*q_product(t_quaternion *q, t_quaternion *p, int inplace)
{
	t_quaternion	*result;
	t_vector		u;
	t_vector		v;
	t_vector		*uv;

	u = (t_vector){q->i, q->j, q->k};
	v = (t_vector){p->i, p->j, p->k};
	result = ft_calloc(1, sizeof(*result));
	uv = v_vector_product(&u, &v);
	if (!result || !uv)
		return (0);
	result->w = (q->w * p->w) - v_dot_product(&u, &v);
	v_scalar_product(q->w, &v, 1);
	v_sum(v_sum(uv, v_scalar_product(p->w, &u, 1), 1), &v, 1);
	if (inplace)
	{
		q->w = result->w;
		free(result);
		result = q;
	}
	result->i = uv->x;
	result->j = uv->y;
	result->k = uv->z;
	free(uv);
	return (result);
}
