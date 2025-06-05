/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:14:21 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/05 14:19:34 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->input_split = NULL;
	shell->cwd = NULL;
	shell->envp = NULL;
	shell->env_v = NULL;
	shell->root = NULL;
	shell->tokens = NULL;
}

void	free_shell_part(t_shell *shell)
{
	if (shell->input)
		free (shell->input);
	if (shell->input_split)
		free (shell->input_split);
	if (shell->cwd)
		free (shell->cwd);
	if (shell->envp)
		clean_matrix(shell->envp);
	reset_shell(shell);
}
