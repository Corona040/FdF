/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/03/30 20:54:44 by ecorona-         ###   ########.fr       */
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

t_grid	*get_grid_from_map(t_map map)
{
	t_grid	*grid;
	char	*aux;
	int		i;
	int		j;

	grid = ft_calloc(1, sizeof(*grid));
	grid->v = create_gridv(map.x, map.y, GRID_STEP);
	grid->color = create_gridc(map.x, map.y);
	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (map.vals[i][j])
		{
			aux = ft_strchr(map.vals[i][j], ',');
			if (aux)
			{
				*aux = '\0';
				grid->color[map.x - j - 1][i] = xatoi(aux + 1);
			}
			grid->v[map.x - j - 1][i].y = -ft_atoi(map.vals[i][j]) * Z_FACTOR;
			j++;
		}
		i++;
	}
	return (grid);
}

int	xatoi(char *hex)
{
	int		result;

	result = 0;
	if (hex[0] != '0' || hex[1] != 'x')
		return (0);
	else
	{
		hex += 2;
		while (*hex)
		{
			if (*hex >= '0' && *hex <= '9')
				result = (result + (*hex - '0')) * 16;
			else if (*hex >= 'A' && *hex <= 'F')
				result = (result + (*hex - 'A' + 10)) * 16;
			else
				return (0);
			hex++;
		}
	}
	return (result / 16);
}
