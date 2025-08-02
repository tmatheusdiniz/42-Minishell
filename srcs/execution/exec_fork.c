/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:15:29 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/24 19:15:35 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_fork(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_code(128 + WTERMSIG(status));
}

void	handle_fork(t_shell *shell, t_fork *frk, int pipe_index)
{
	frk->pid[pipe_index] = fork();
	if (frk->pid[pipe_index] == 0)
		set_pipe(frk, pipe_index);
	else if (frk->pid[pipe_index] > 0)
		return ;
	else
		handle_errors(shell, "fork failed!", errno);
}

void	execute_no_pipe(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (find_executable(shell, (t_exec *)shell->root,
				((t_exec *)shell->root)->argv[0]) == 0)
			execve(((t_exec *)shell->root)->cmd_path,
				((t_exec *)shell->root)->argv, shell->envp);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_exec *)shell->root)->argv[0], 2);
			ft_putendl_fd(": command not found", 2);
			free_shell_final(shell);
			exit(127);
		}
	}
	else if (pid > 0)
		aux_fork(pid, status);
}
