/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/09 19:56:11 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env_v(t_env_v *env_v)
{
	t_env_v	*current;
	t_env_v	*next;

	current = env_v;
	while (current)
	{
		next = current->next;
		if (current->key)
			free (current->key);
		if (current->value)
			free (current->value);
		free(current);
		current = next;
	}
}

void	free_shell_final(t_shell *shell)
{
	if (!shell)
		return ;
	free_shell_part(shell);
	if (shell->envp)
	{
		clean_matrix(shell->envp);
		shell->envp = NULL;
	}
	if (shell->env_v)
	{
		free_env_v(shell->env_v);
		shell->env_v = NULL;
	}
	free(shell);
}
