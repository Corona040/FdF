/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:59:31 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 10:18:35 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	**create_gridv(int width, int height, float_t step)
{
	t_vector	**grid;
	int			i;

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
	step_gridv(grid, width, height, step);
	return (grid);
}

t_vector	**step_gridv(t_vector **grid, int width, int height, float_t step)
{
	t_vector	value;
	int			i;
	int			j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			value = (t_vector){i * step - (step * width) / 2 + step / 2, \
				0, \
				j * step - (step * height) / 2 + step / 2};
			v_assign(&grid[i][j], value, 1);
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
