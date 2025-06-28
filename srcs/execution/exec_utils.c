/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:02:31 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/22 19:10:10 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_lastcmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index)
{
	if (*(int *)root == BT || *(int *)root == EXEC)
			ft_execute_cmmd(shell, root, frk, pipe_index);
	// after add checks to other types of input
}

void	check_bt(t_shell *shell, t_exec *exec_node)
{
	// after i will need to clean it in fail case
	if (!exec_node)
		malloc_failure(shell, "check_command");
	if (!ft_strncmp(exec_node->argv[0], "cd", ft_strlen(exec_node->argv[0])))
		ft_cd(shell, exec_node);
	else if (!ft_strncmp(exec_node->argv[0], "pwd", ft_strlen(exec_node->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(exec_node->argv[0], "echo", ft_strlen(exec_node->argv[0])))
		ft_echo(exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "env", ft_strlen(exec_node->argv[0])))
		ft_env(shell->envp, exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "unset", ft_strlen(exec_node->argv[0])))
		ft_unset(shell, exec_node->argv + 1);
	else if (!(ft_strncmp(exec_node->argv[0], "export", ft_strlen(exec_node->argv[0]))))
		ft_export(shell, exec_node->argv);
	else if (!(ft_strncmp(exec_node->argv[0], "exit", ft_strlen(exec_node->argv[0]))))
		ft_exit(shell, exec_node);
	else
	{
		ft_putstr_fd(exec_node->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
}
