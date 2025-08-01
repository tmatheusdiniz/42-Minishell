/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:02:31 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/23 11:25:02 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_checkbt(t_shell *shell, t_exec *exec_node);
static void	aux_fork(pid_t pid, int status);

void	aux_execution(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
	else if (*(int *)root == OUTREDIR)
		exec_outredir(shell, shell->root, frk, pipe_index);
	else if (*(int *)root == INREDIR)
		exec_inredir(shell, shell->root, frk, pipe_index);
	else if (*(int *)root == APPEND)
		exec_append(shell, root, frk, pipe_index);
	else if (*(int *)root == HEREDOC)
		exec_heredoc(shell, root, frk, pipe_index);
}

void	aux_no_pipe(t_shell *shell, t_fork *frk, void *root)
{
	if (!frk )
		frk = handle_pipe(shell, shell->root);

	if (*(int *)shell->root == EXEC)
		execute_no_pipe(shell);
	else if(*(int *)shell->root == BT)
		check_bt(shell, root);
	else if (*(int *)shell->root == OUTREDIR)
		exec_outredir(shell, root, frk, -4);
	else if (*(int *)shell->root == INREDIR)
		exec_inredir(shell, root, frk, -4);
	else if (*(int *)shell->root == APPEND)
		exec_append(shell, root, frk, -4);
	else if (*(int *)root == HEREDOC)
		exec_heredoc(shell, root, frk, -4);
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

static void	aux_fork(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_code(128 + WTERMSIG(status));
}

void	check_bt(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node)
		malloc_failure(shell, "check_bt");
	if (!ft_strncmp(exec_node->argv[0], "cd",
			ft_strlen(exec_node->argv[0])))
		ft_cd(shell, exec_node);
	else if (!ft_strncmp(exec_node->argv[0], "pwd",
			ft_strlen(exec_node->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(exec_node->argv[0], "echo",
			ft_strlen(exec_node->argv[0])))
		ft_echo(exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "env",
			ft_strlen(exec_node->argv[0])))
		ft_env(shell->envp, exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "unset",
			ft_strlen(exec_node->argv[0])))
		ft_unset(shell, exec_node->argv + 1);
	else
		aux_checkbt(shell, exec_node);
}

static void	aux_checkbt(t_shell *shell, t_exec *exec_node)
{
	if (!(ft_strncmp(exec_node->argv[0], "export",
				ft_strlen(exec_node->argv[0]))))
		ft_export(shell, exec_node->argv);
	else if (!(ft_strncmp(exec_node->argv[0], "exit",
				ft_strlen(exec_node->argv[0]))))
		ft_exit(shell, exec_node);
	else
	{
		ft_putstr_fd(exec_node->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_code(127);
	}
}
