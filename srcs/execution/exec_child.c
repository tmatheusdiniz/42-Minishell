/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:26 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/08 16:48:46 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_child_process(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	char	*cmd_path;
	char	**argv;

	argv = prepare_argv_for_exec(exec_node->argv);
	if (!argv)
	{
		child_cleanup(shell, frk);
		exit(126);
	}
	cmd_path = exec_node->cmd_path;
	execve(cmd_path, argv, shell->envp);
	clean_matrix(argv);
	child_cleanup(shell, frk);
	exit(126);
}

static void	handle_exec_error(t_shell *shell, t_exec *exec_node,
		t_fork *frk, int error_code)
{
	if (error_code == 127)
		print_command_notf(exec_node->argv[0]);
	child_cleanup(shell, frk);
	exit(127);
}

void	handle_exec_child(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	int	exec_result;

	exec_result = find_executable(shell, exec_node, exec_node->argv[0]);
	if (exec_result != 0)
		handle_exec_error(shell, exec_node, frk, exec_result);
	else
		exec_child_process(shell, exec_node, frk);
}

void	handle_builtin_child(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	check_bt(shell, exec_node, frk);
	child_cleanup(shell, frk);
	exit(exit_code(-1));
}
