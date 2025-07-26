/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:49:38 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/23 11:30:22 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_execution(t_shell *shell)
{
	t_fork	*frk;
	int		i;
	int		last_exit_code;

	i = 0;
	last_exit_code = 0;
	if (*(int *)shell->root == PIPE)
	{
		frk = handle_pipe(shell, shell->root);
		execute_tree_recur(shell, shell->root, frk, 0);
		while (i < frk->nbr_cmds - 1)
		{
			close (frk->pipe[i][0]);
			close (frk->pipe[i][1]);
			i ++;
		}
		last_exit_code = complete_execution(frk);
		exit_code(last_exit_code);
		cleanup_fork_fds(frk);
	}
	else
		aux_execution(shell, shell->root);
}

void	ft_execute_cmmd(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)root;
	handle_fork(shell, frk, pipe_index);
	if (frk->pid[pipe_index] > 0)
		return ;
	if (*(int *)root == EXEC)
	{
		if (find_executable(shell, (t_exec *)root, ((t_exec *)root)->argv[0]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_exec *)root)->argv[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
		else
			execve(exec_node->cmd_path, exec_node->argv, shell->envp);
		error_message("EXECV", 0);
		exit(126);
	}
	else if (*(int *)root == BT)
	{
		check_bt(shell, exec_node);
		exit (0);
	}
}

void	execute_tree_recur(t_shell *shell, void *root,
		t_fork *frk, int pipe_index)
{
	t_pipe	*pipe_root;

	if (!root)
		return ;
	if (*(int *)root == PIPE)
	{
		pipe_root = (t_pipe *)root;
		execute_tree_recur(shell, pipe_root->left, frk, pipe_index);
		execute_tree_recur(shell, pipe_root->right, frk, pipe_index + 1);
	}
	else if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
	else if (*(int *)root == OUTREDIR || *(int *)root == INREDIR
		|| *(int *)root == APPEND || *(int *)root == HEREDOC)
	{
		handle_fork(shell, frk, pipe_index);
		if (frk->pid[pipe_index] == 0)
		{
			aux_execution(shell, root);
			exit(0);
		}
	}
}
