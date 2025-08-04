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

static void	aux_checkbt(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	if (!(ft_strncmp(exec_node->argv[0], "export",
				ft_strlen(exec_node->argv[0]))))
		ft_export(shell, exec_node->argv);
	else if (!(ft_strncmp(exec_node->argv[0], "exit",
				ft_strlen(exec_node->argv[0]))))
		ft_exit(shell, exec_node, frk);
	else
	{
		ft_putstr_fd(exec_node->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_code(127);
	}
}

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
	t_fork	*local_frk;

	local_frk = frk;
	if (!frk)
		local_frk = handle_pipe(shell, shell->root);
	if (*(int *)shell->root == EXEC)
		execute_no_pipe(shell, local_frk);
	else if (*(int *)shell->root == BT)
		check_bt(shell, root, local_frk);
	else if (*(int *)shell->root == OUTREDIR)
		exec_outredir(shell, root, local_frk, -4);
	else if (*(int *)shell->root == INREDIR)
		exec_inredir(shell, root, local_frk, -4);
	else if (*(int *)shell->root == APPEND)
		exec_append(shell, root, local_frk, -4);
	else if (*(int *)root == HEREDOC)
		exec_heredoc(shell, root, local_frk, -4);
	if (!frk && local_frk)
		cleanup_fork(local_frk);
}

void	check_bt(t_shell *shell, t_exec *exec_node, t_fork *frk)
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
		aux_checkbt(shell, exec_node, frk);
}
