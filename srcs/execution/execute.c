/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:49:38 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/21 21:54:55 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_execution(t_shell *shell)
{
	int	i;
	t_fork	*frk;

	i = 0;
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
		i = 0;
		while (i < frk->nbr_cmds)
			waitpid(frk->pid[i++], NULL, 0);
		cleanup_fork_fds(frk);
	}
	else
		aux_execution(shell);
}

void	ft_execute_cmmd(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	t_exec *exec_node;

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

void	execute_tree_recur(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	t_pipe	*pipe_root;

	if (!root)
		return;
	if (*(int *)root == PIPE)
	{
		pipe_root = (t_pipe *)root;
		execute_tree_recur(shell, pipe_root->left, frk, pipe_index);
		execute_tree_recur(shell, pipe_root->right, frk, pipe_index + 1);
	}
	else if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
}
