/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:19:30 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/04 10:52:56 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

t_vector	*v_assign(t_vector *u, t_vector v, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (NULL);
	}
	result->x = v.x;
	result->y = v.y;
	result->z = v.z;
	return (result);
}

t_vector	*v_sum(t_vector *u, t_vector *v, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (NULL);
	}
	result->x = u->x + v->x;
	result->y = u->y + v->y;
	result->z = u->z + v->z;
	return (result);
}

float_t	v_module(t_vector *u)
{
	return (sqrtf(fabsf(v_dot_product(u, u))));
}

float_t	v_distance(t_vector *u, t_vector *v)
{
	t_vector	diff;

	diff.x = u->x - v->x;
	diff.y = u->y - v->y;
	diff.z = u->z - v->z;
	return (v_module(&diff));
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
			return (NULL);
	}
	module = v_module(u);
	result->x = u->x / module;
	result->y = u->y / module;
	result->z = u->z / module;
	return (result);
}
