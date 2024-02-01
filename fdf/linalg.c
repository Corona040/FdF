/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:00:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/01 17:44:57 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_vector	*v_assign(t_vector *u, t_vector v, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("scalar_product fail\n");
	}
	result->x = v.x;
	result->y = v.y;
	result->z = v.z;
	return (result);
}

float_t	distance(t_vector *u, t_vector *v)
{
	t_vector	diff;

	diff.x = u->x - v->x;
	diff.y = u->y - v->y;
	diff.z = u->z - v->z;
	return (v_module(&diff));
}

float_t	dot_product(t_vector *u, t_vector *v)
{
	float_t	result;

	result = 0;
	result += u->x * v->x;
	result += u->y * v->y;
	result += u->z * v->z;
	return (result);
}

t_vector	*scalar_product(float_t a, t_vector *u, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("scalar_product fail\n");
	}
	result->x = a * u->x;
	result->y = a * u->y;
	result->z = a * u->z;
	return (result);
}

t_vector	*vector_product(t_vector *u, t_vector *v)
{
	t_vector	*result;

	result = ft_calloc(1, sizeof(*result));
	if (!result)
		ft_printf("scalar_product fail\n");
	result->x = (u->y * v->z) - (u->z * v->y);
	result->y = (u->z * v->x) - (u->x * v->z);
	result->z = (u->x * v->y) - (u->y * v->x);
	return (result);
}

float_t	v_module(t_vector *u)
{
	return (sqrtf(fabsf(dot_product(u, u))));
}

t_vector	*v_proj(t_vector *a, t_vector *b, int inplace)
{
	t_vector	*result;
	t_vector	*temp;
	float_t		k;

	if (inplace)
		result = a;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("scalar_product fail\n");
	}
	k = v_module(b);
	k = dot_product(a, b) / (k * k);
	temp = a;
	result = scalar_product(k, b, 0);
	if (inplace)
		free(temp);
	return (result);
}

t_vector	*v_planeproj(t_vector *u, int axis, int inplace)
{
	t_vector	*result;
	t_vector	*proj;
	t_vector	normal;

	if (axis == 1)
		normal = (t_vector) {.x = 0, .y = 0, .z = 1};
	if (axis == 2)
		normal = (t_vector) {.x = 0, .y = 1, .z = 0};
	if (axis == 3)
		normal = (t_vector) {.x = 1, .y = 0, .z = 0};
	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("scalar_product fail\n");
	}
	proj = v_proj(u, &normal, 0);
	result->x = u->x;
	result->y = u->y;
	result->z = u->z;
	result->x -= proj->x;
	result->y -= proj->y;
	result->z -= proj->z;
	free(proj);
	return (result);
}

t_vector	*v_rotate(t_vector *u, float_t a, int axis, int inplace)
{
	t_vector	*result;
	t_vector	temp;

	if (inplace)
		result = u;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			ft_printf("scalar_product fail\n");
	}
	temp.x = u->x;
	temp.y = u->y;
	temp.z = u->z;
	if (axis == 1)
	{
		result->x = temp.x * cosf(a) - temp.y * sinf(a);
		result->y = temp.x * sinf(a) + temp.y * cosf(a);
		result->z = temp.z;
	}
	else if (axis == 2)
	{
		result->x = temp.x * cosf(a) + temp.z * sinf(a);
		result->y = temp.y;
		result->z = -temp.x * sinf(a) + temp.z * cosf(a);
	}
	else if (axis == 3)
	{
		result->x = temp.x;
		result->y = temp.y * cosf(a) - temp.z * sinf(a);
		result->z = temp.y * sinf(a) + temp.z * cosf(a);
	}
	return (result);
}
