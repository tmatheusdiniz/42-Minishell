/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:50:12 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/08 17:02:14 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_no_pipe_child(t_shell *shell, t_fork *frk)
{
	t_exec	*exec_node;
	int		exec_result;

	exec_node = (t_exec *)shell->root;
	exec_result = find_executable(shell, exec_node, exec_node->argv[0]);
	if (exec_result == 0)
	{
		execve(exec_node->cmd_path, exec_node->argv, shell->envp);
		handle_errors(shell, "EXECV ERROR", 0);
		exit(126);
	}
	else if (exec_result == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec_node->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		child_cleanup(shell, frk);
		exit(127);
	}
	else
	{
		child_cleanup(shell, frk);
		exit(exec_result);
	}
}

void	execute_no_pipe(t_shell *shell, t_fork *frk)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_no_pipe_child(shell, frk);
	else if (pid > 0)
		aux_fork(pid);
	else
		handle_errors(shell, "fork failed!", errno);
}
