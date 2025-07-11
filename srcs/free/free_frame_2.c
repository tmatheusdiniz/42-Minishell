/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:52:45 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/06 15:55:38 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
}

void	cleanup_fork_fds(t_fork *frk)
{
	int	i;

	if (!frk || !frk->pipe)
		return ;
	i = 0;
	while (i < frk->nbr_cmds - 1)
	{
		if (frk->pipe[i])
		{
			close(frk->pipe[i][0]);
			close(frk->pipe[i][1]);
			free(frk->pipe[i]);
		}
		i++;
	}
	free(frk->pipe);
	if (frk->pid)
		free(frk->pid);
	free(frk);
}

void	cleanup_parsing_error(t_shell *shell)
{
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

void	cleanup_execution_error(t_shell *shell, t_fork *frk)
{
	if (frk)
		cleanup_fork_fds(frk);
	free_shell_part(shell);
}
