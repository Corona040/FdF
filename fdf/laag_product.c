/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_product.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:20:09 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/04 10:56:55 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

t_vector	*v_scalar_product(float_t a, t_vector *u, int inplace)
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
	result->x = a * u->x;
	result->y = a * u->y;
	result->z = a * u->z;
	return (result);
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

t_vector	*v_vector_product(t_vector *u, t_vector *v)
{
	t_vector	*result;

	result = ft_calloc(1, sizeof(*result));
	if (!result)
		return (NULL);
	result->x = (u->y * v->z) - (u->z * v->y);
	result->y = (u->z * v->x) - (u->x * v->z);
	result->z = (u->x * v->y) - (u->y * v->x);
	return (result);
}
