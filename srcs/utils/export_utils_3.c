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

#include <minishell.h>

void	update_envp_append(t_shell *shell, char *key, char *append)
{
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], key, ft_strlen(key)))
		{
			shell->envp[i] = ft_strjoin(shell->envp[i], append);
			if (!shell->envp[i])
				malloc_failure(shell, "update_envp_append");
			if (!shell->envp[i])
				malloc_failure(shell, "key");
			if (append)
				free (append);
			if (key)
				free (key);
			break ;
		}
		i++;
	}
}
