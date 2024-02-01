/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:00:16 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/01 15:12:31 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

typedef struct vector
{
	float_t x;
	float_t y;
	float_t z;
}	t_vector;

float_t	dot_product(t_vector *u, t_vector *v)
{
	float_t	result;

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
}

float_t f_abs(float_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}
