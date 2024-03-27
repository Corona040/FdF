/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/03/27 20:12:39 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// should return grid_x, grid_y and z_vals -> map struct with dim and vals
//		(dim attribute)
// line and z_val have allocs -> need free
// also needs colors for points
int read_map(char *path)
{
	int		grid_x;
	int		grid_y;
	int		z_val;
	int		z_vals;
	char	*line;

	grid_y = 0;
	grid_x = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd > 2)
	{
		grid_y = 0;
		line = get_next_line(fd);
		while (line)
		{
			z_val = ft_split(line, ' ');
			free(line);
			z_vals[grid_y] = z_val;
			grid_y++;
			line = get_next_line(fd);
			grid_x = 0;
			while (z_val[grid_x])
			{
				// free(z_val[grid_x]);
				grid_x++;
			}
			// free(z_val);
		}
	}
	close(fd);
	// return (map structure);
}

// illegal "for" 🚨🚨🚨🚓🚓🚓
int get_colors_i_think_prolly(void) //grid?
{
	int		grid_y;
	int		**z_vals;
	char	*aux;
	// grid??

	for (int i = 0; i < grid_y; i++)
	{
		for (int j = 0; z_vals[i][j]; j++)
		{
			aux = ft_strchr(z_vals[i][j], ',');
			if (aux)
				*aux = '\0';
			grid[grid_x - j - 1][i].y = -ft_atoi(z_vals[i][j]) * Z_FACTOR;
		}
	}
}

/*
 * create win img whatever
 */
