/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:59:31 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 08:59:41 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	**create_gridv(int width, int height, float_t step)
{
	t_vector	**grid;
	int			i;
	int			j;

	grid = ft_calloc(width, sizeof(t_vector *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < width)
	{
		grid[i] = ft_calloc(height, sizeof(**grid));
		if (!grid[i++])
			return (NULL);
	}
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			v_assign(&grid[i][j], (t_vector){i * (float_t)step - ((float_t)(step * width) / 2) + (float_t)step / 2, 0, j * (float_t)step - ((float_t)(step * height) / 2) + (float_t)step / 2}, 1);
			j++;
		}
		i++;
	}
	return (grid);
}

t_rgb	**create_gridc(int width, int height)
{
	t_rgb	**grid;
	int		i;

	grid = ft_calloc(width, sizeof(int *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < width)
	{
		grid[i] = ft_calloc(height, sizeof(**grid));
		if (!grid[i++])
			return (NULL);
	}
	return (grid);
}
