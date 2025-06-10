/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:14:21 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/09 18:59:28 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->input_split = NULL;
	shell->cwd = NULL;
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
	reset_shell(shell);
}
