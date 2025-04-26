/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:34 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/26 21:27:30 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i ++;
	return (s1[i] - s2[i]);
}

void	ft_sort_params(char **arg, int argc)
{
	int		i;
	int		j;
	char	*save;

	i = 1;
	j = 1;
	while (j < argc)
	{
		i = 1;
		while (i < argc)
		{
			if (arg[i + 1] && ft_strcmp(arg[i], arg[i + 1]) > 0)
			{
				save = arg[i];
				arg[i] = arg[i + 1];
				arg[i + 1] = save;
			}
			i ++;
		}
		j ++;
	}
}
