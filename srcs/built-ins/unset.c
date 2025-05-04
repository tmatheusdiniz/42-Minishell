/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:22:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 00:24:45 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->envp[i])
		i++;
	return (i);
}

char	**new_env(t_mini *mini, int index_to_unset)
{
	int		i;
	int		h;
	int		size_of_env;
	char	**changed_env;

	size_of_env = size_env(mini);
	changed_env = (char **)ft_calloc(sizeof(char *), size_of_env);
	if (!changed_env)
		return (NULL);
	h = 0;
	i = 0;
	while (mini->envp[i])
	{
		if (i == index_to_unset)
			i++;
		changed_env[h] = (char *)ft_calloc(sizeof(char), ft_strlen(mini->envp[i]));
		if (!changed_env[h])
			return (NULL);
		changed_env[h++] = ft_strdup(mini->envp[i++]);
	}
	free(mini->envp);
	changed_env[h] = NULL;
	return (changed_env);
}

int	unset(t_mini *mini, char *var)
{
	int	index_to_unset;
	int	i;

	if (!var)
		return (0);
	index_to_unset = get_index_env(mini, var);
	if (index_to_unset == -1)
		return (0);
	i = 0;
	while (mini->envp[i])
	{
		if (i == index_to_unset)
			free(mini->envp[index_to_unset]);
		i++;
	}
	mini->envp = new_env(mini, index_to_unset);
	return (0);
}
