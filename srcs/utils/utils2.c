/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:57:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/18 16:45:30 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_other_chars(char *var)
{
	int		i;
	char	new_var[999];
	int		j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (ft_isalpha(var[i]))
			new_var[j++] = var[i++];
		else
			i++;
	}
	new_var[j] = '\0';
	return (ft_strdup(new_var));
}

char	*clean_quotes(char *var)
{
	int		i;
	char	new_var[999];
	int		j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] != 39 && var[i] != 34)
			new_var[j++] = var[i++];
		else
			i++;
	}
	new_var[j] = '\0';
	return (ft_strdup(new_var));
}
