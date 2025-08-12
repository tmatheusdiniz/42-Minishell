/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:31:00 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/02 13:31:12 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>

static void	aux_set_aux(t_shell *shell, char *old_value, char *key, char **splt)
{
	if (!old_value)
		add_var_envp(shell, splt[0], ft_strchr(key, '='));
	else
		update_envp_append(shell, splt[0], splt[1]);
}

void	update_envp_append(t_shell *shell, char *key, char *append)
{
	int		i;
	char	*prefix;
	char	*new_value;
	char	*old_value;

	i = 0;
	prefix = ft_strjoin(key, "=");
	if (!prefix)
		malloc_failure(shell, "update_env_append");
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], prefix, ft_strlen(prefix)))
		{
			old_value = shell->envp[i];
			new_value = ft_strjoin(shell->envp[i], append);
			if (!shell->envp[i])
				malloc_failure(shell, "update_envp_append");
			shell->envp[i] = new_value;
			free (old_value);
			break ;
		}
		i++;
	}
	free (prefix);
}

char	*aux_set_with_append(t_shell *shell, t_env_v *current,
		char **splt, char *key)
{
	char	*old_value;

	old_value = NULL;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, splt[0]) == 0)
		{
			(splt[1])++;
			if (current->value)
			{
				old_value = ft_strdup(current->value);
				free (current->value);
			}
			if (!old_value)
				current->value = ft_strdup(splt[1]);
			else
				current->value = ft_strjoin(old_value, splt[1]);
			if (!current->value)
				malloc_failure(shell, "set_with_append");
			aux_set_aux(shell, old_value, key, splt);
		}
		current = current->next;
	}
	return (old_value);
}
