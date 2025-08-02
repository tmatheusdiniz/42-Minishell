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
