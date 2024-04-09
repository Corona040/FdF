/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:08:47 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/09 21:46:23 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_failure(t_map *map)
{
	free_map(map);
	exit(EXIT_FAILURE);
}

void	grid_to_map(t_grid *grid, t_map *map)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (map->vals[i][j])
		{
			aux = ft_strchr(map->vals[i][j], ',');
			grid->c[map->x - j - 1][i] = itoc(0xFFFFFF);
			if (aux)
			{
				*aux = '\0';
				grid->c[map->x - j - 1][i] = itoc(xatoi(aux + 1));
			}
			grid->v[map->x - j - 1][i].y = -ft_atoi(map->vals[i][j]) * Z_FACTOR;
			j++;
		}
		i++;
	}
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
			else if (*hex >= 'a' && *hex <= 'f')
				result = (result + (*hex - 'a' + 10)) * 16;
			else
				return (0);
			hex++;
		}
	}
	return (result / 16);
}

t_rgb	itoc(int i)
{
	t_rgb	rgb;

	rgb.r = (i & 0xFF0000) / (256 * 256);
	rgb.g = (i & 0x00FF00) / (256);
	rgb.b = i & 0x0000FF;
	return (rgb);
}

int	ctoi(t_rgb rgb)
{
	int	i;

	i = 0;
	i += rgb.r * 256 * 256;
	i += rgb.g * 256;
	i += rgb.b;
	return (i);
}
