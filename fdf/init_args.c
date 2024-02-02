/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 17:02:49 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/02 16:19:50 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	leave(t_arg *arg, int **stack, int error, int error_status)
{
	if (error)
		ft_printf("Error\n");
	if (arg)
		free_argv(arg);
	if (stack)
		free_stack(stack);
	exit(error_status);
}

void	free_argv(t_arg *arg)
{
	int	i;

	if (arg->free)
	{
		i = 0;
		while (i < arg->c)
		{
			if (arg->ptr_v[i])
				free(arg->ptr_v[i]);
			i++;
		}
		if (arg->v)
			free(arg->v);
		if (arg->ptr_v)
			free(arg->ptr_v);
	}
}

void	split_argv(t_arg *arg)
{
	int	i;

	arg->v = ft_split(arg->v[1], ' ');
	if (!arg->v)
		leave(arg, NULL, 1, EXIT_FAILURE);
	arg->free = 1;
	arg->c = 0;
	while (arg->v[arg->c])
		arg->c++;
	arg->ptr_v = ft_calloc(arg->c, sizeof(char *));
	if (!arg->ptr_v)
		leave(arg, NULL, 1, EXIT_FAILURE);
	i = 0;
	while (i < arg->c)
	{
		arg->ptr_v[i] = arg->v[i];
		i++;
	}
}

void	check_args(t_arg *arg, int zeros, int i, int j)
{
	if (arg->c == 0)
		leave(arg, NULL, 0, EXIT_SUCCESS);
	while (i < arg->c)
	{
		j = i;
		while (++j < arg->c)
			if ((!ft_strncmp(arg->v[i], arg->v[j], ft_strlen(arg->v[i])) \
				&& !ft_strncmp(arg->v[i], arg->v[j], ft_strlen(arg->v[j]))) \
				|| (zeros && arg->v[i][arg->v[i][0] == '-'] == '0' \
				&& arg->v[j][arg->v[j][0] == '-'] == '0'))
				leave(arg, NULL, 1, EXIT_SUCCESS);
		j = ((arg->v[i][0] == '-') && (arg->v[i][1] != 0)) - 1;
		while (arg->v[i][++j] != 0)
			if (!ft_isdigit(arg->v[i][j]) \
					|| ((j > 9 + (arg->v[i][0] == '-')) && zeros))
				leave(arg, NULL, 1, EXIT_SUCCESS);
		if (arg->v[i][0] == '-' && --j == 10)
			if (ft_strncmp(arg->v[i], "-2147483648", 12) > 0)
				leave(arg, NULL, 1, EXIT_SUCCESS);
		if (arg->v[i][0] != '-' && --j == 9)
			if (ft_strncmp(arg->v[i], "2147483647", 12) > 0)
				leave(arg, NULL, 1, EXIT_SUCCESS);
		i++;
	}
}

void	init_args(t_arg *arg, int is_neg, int idx)
{
	if (arg->c == 2 && ft_strchr(arg->v[1], ' '))
		split_argv(arg);
	else
	{
		arg->c = arg->c - 1;
		arg->v = arg->v + 1;
	}
	while (++idx < arg->c)
		if (arg->v[idx][0] == '+' && arg->v[idx][1] != '\0' \
			&& arg->v[idx][1] != '-')
			arg->v[idx]++;
	check_args(arg, 0, 0, 0);
	idx = -1;
	while (++idx < arg->c)
	{
		if (arg->v[idx][0] == '-')
			is_neg = 1;
		while (arg->v[idx][0 + is_neg] == '0' && arg->v[idx][0 + is_neg + 1])
			arg->v[idx]++;
		if (is_neg)
			arg->v[idx][0] = '-';
		is_neg = 0;
	}
	check_args(arg, 1, 0, 0);
}
