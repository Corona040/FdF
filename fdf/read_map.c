/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/03/30 18:58:59 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// line and z_val have allocs -> need free
t_map	read_map_file(char *path)
{
	t_map	map;
	int		fd;
	char	**z_val;
	char	*line;

	map.y = 0;
	map.x = 0;
	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		map.y = 0;
		line = get_next_line(fd);
		while (line)
		{
			z_val = ft_split(line, ' ');
			free(line);
			map.vals[map.y] = z_val;
			map.y++;
			line = get_next_line(fd);
			map.x = 0;
			while (z_val[map.x])
			{
				// free(z_val[grid_x]);
				map.x++;
			}
			// free(z_val);
		}
	}
	else
	{
		close(fd);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	return (map);
}

t_vector	**get_grid_from_map(t_map map)
{
	char		*aux;
	t_vector	**grid;
	int			i;
	int			j;

	grid = create_grid(map.x, map.y, GRID_STEP);
	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (map.vals[i][j])
		{
			aux = ft_strchr(map.vals[i][j], ',');
			if (aux)
				*aux = '\0';
			grid[map.x - j - 1][i].y = -ft_atoi(map.vals[i][j]) * Z_FACTOR;
			j++;
		}
		i++;
	}
	return (grid);
}
