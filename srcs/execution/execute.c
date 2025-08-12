/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:49:38 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/08 16:49:24 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>
#include <sys/wait.h>
#include <unistd.h>

static int	complete_execution(t_fork *frk)
{
	int	status;
	int	i;
	int	last_exit_code;

	i = 0;
	last_exit_code = 0;
	while (i < frk->nbr_cmds)
	{
		waitpid(frk->pid[i], &status, 0);
		if (i == frk->nbr_cmds - 1)
		{
			if (WIFEXITED(status))
				last_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_exit_code);
}

static void	close_all_pipes(t_fork *frk)
{
	int	i;

	i = 0;
	while (i < frk->nbr_cmds - 1)
	{
		close(frk->pipe[i][0]);
		close(frk->pipe[i][1]);
		i++;
	}
}

static void	exec_with_pipes(t_shell *shell)
{
	t_fork	*frk;
	int		last_exit_code;

	frk = handle_pipe(shell, shell->root);
	execute_tree_recur(shell, shell->root, frk, 0);
	close_all_pipes(frk);
	last_exit_code = complete_execution(frk);
	exit_code(last_exit_code);
	cleanup_fork(frk);
}

void	ft_execution(t_shell *shell)
{
	t_fork	*frk;

	frk = NULL;
	if (*(int *)shell->root == PIPE)
		exec_with_pipes(shell);
	else
		aux_no_pipe(shell, frk, shell->root);
}

void	ft_execute_cmmd(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)root;
	handle_fork(shell, frk, pipe_index);
	if (frk->pid[pipe_index] > 0)
		return ;
	if (*(int *)root == EXEC)
		handle_exec_child(shell, exec_node, frk);
	else if (*(int *)root == BT)
		handle_builtin_child(shell, exec_node, frk);
	exit(exit_code(-1));
}
