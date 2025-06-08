/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/07 01:08:14 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <minishell.h>

static void	reset_for_exit(t_shell *shell)
{
	shell->input = NULL;
	shell->input_split = NULL;
	shell->cwd = NULL;
	shell->trimmed = NULL;
	shell->root = NULL;
	shell->tokens = NULL;
	shell->envp = NULL;
	shell->env_v = NULL;
}

static void	free_env_v(t_env_v *env_v)
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

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->input)
			free (shell->input);
		if (shell->trimmed)
			free (shell->trimmed);
		if (shell->cwd)
			free (shell->cwd);
		if (shell->input_split)
			clean_matrix(shell->input_split);
		if (shell->envp)
			clean_matrix(shell->envp);
		if (shell->env_v)
			free_env_v(shell->env_v);
	}
	reset_for_exit(shell);
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
