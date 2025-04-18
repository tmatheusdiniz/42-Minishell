/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 20:25:19 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**duplicate_env(char **envp)
{
	char	**duplicate;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	duplicate = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		duplicate[i] = ft_strdup(envp[i]);
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

int	env(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
