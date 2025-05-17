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

#include <minishell.h>

char	**duplicate_env_v(char **envp)
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

char	*check_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
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
