/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/01 16:24:20 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_index_env(t_mini *mini, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(var);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var, len) == 0 && mini->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*check_space(char *input)
{
	int	i;

	i = 0;
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
	{
		i++;
	}
	return (&input[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i ++;
	return (s1[i] - s2[i]);
}
