/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:52:45 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 23:13:57 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*start;

	if (!tokens || !*tokens)
		return ;
	start = *tokens;
	while (start && start->prev)
		start = start->prev;
	current = start;
	while (current)
	{
		next = current->next;
		if (current->token)
		{
			free(current->token);
			current->token = NULL;
		}
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	cleanup_fork(t_fork *frk)
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
		free_tokens(&shell->tokens);
		shell->tokens = NULL;
	}
}

void	cleanup_execution_error(t_shell *shell, t_fork *frk)
{
	if (frk)
		cleanup_fork(frk);
	free_shell_part(shell);
}
