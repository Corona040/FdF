/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:25:30 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/09 21:47:59 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_zval(char **zval, int *n_nl)
{
	int	i;
	int	after_comma;

	while (*zval)
	{
		after_comma = 0;
		i = 0;
		if ((*zval)[i] == '\n')
			(*n_nl)++;
		while ((*zval)[i])
		{
			if (!after_comma && !ft_isint((*zval)[i]) && (*zval)[i] != '\n')
			{
				if ((*zval)[i] == ',' && ft_ishexflag(&((*zval)[i + 1])))
					skip_comma(&i, &after_comma);
				else
					return (-1);
			}
			else if (after_comma && !ft_ishex((*zval)[i]) && (*zval)[i] != '\n')
				return (-1);
			i++;
		}
		zval++;
	}
	return (0);
}

int	ft_ishex(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'f')
		return (1);
	if (c >= 'A' && c <= 'F')
		return (1);
	return (0);
}

int	ft_ishexflag(char *s)
{
	if (s[0] == '0' && s[1] == 'x')
		return (1);
	return (0);
}

int	ft_isint(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

void	skip_comma(int *i, int *after_comma)
{
	*i += 3;
	*after_comma = 1;
}
