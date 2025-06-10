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

#include "libft.h"
#include <minishell.h>

int	add_var_envp(char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp[i])
		i ++;
	envp[i] = (char *)malloc(sizeof(char *) * ft_strlen(new_var));
	if (!envp[i])
		return (1);
	return (0);
}

int	remove_var_envp(char **envp, char *key)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (!ft_strcmp(envp[i], key) && envp[i][len] == '=')
		{
			free (envp[i]);
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j ++;
			}
		}
		else
			i ++;
	}
	return (0);
}

char **duplicate_envp(char **envp)
{
	int	i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i ++;
	new_envp = (char **)malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp)
		{
			while (--i >= 0)
				free (new_envp[i]);
			return (free(new_envp), NULL);
		}
		i ++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_env(char **envp, char **arguments)
{
	int	i;

	if (arguments[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}
