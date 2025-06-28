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

static void	check_lastcmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index)
{
	if (*(int *)root == BT || *(int *)root == EXEC)
			ft_execute_cmmd(shell, root, frk, pipe_index);
	// after add checks to other types of input
}

void	set_pipe(t_fork *frk, int pipe_index)
{
	int	i;

	i = 0;
	while (i < frk->nbr_cmds - 1)
	{
		if (i != pipe_index - 1)
			close (frk->pipe[i][0]);
		if (i != pipe_index)
			close (frk->pipe[i][1]);
		i ++;
	}
	if (pipe_index > 0)
	{
		dup2(frk->pipe[pipe_index - 1][0], STDIN_FILENO);
		close(frk->pipe[pipe_index - 1][0]);
	}
	if (pipe_index < frk->nbr_cmds - 1)
	{
		dup2(frk->pipe[pipe_index][1], STDOUT_FILENO);
		close(frk->pipe[pipe_index][1]);
	}
}

bool	check_pipe_rgt(void	*root)
{
	int	*type_right;

	type_right = (int *)((t_pipe *)root)->right;
	if (type_right)
	{
		if (*type_right == PIPE)
			return (true);
	}
	return (false);
}

void	check_bt(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	(void)frk; // after i will need to clean it in fail case
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

void	execute_tree_recur(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	t_pipe	*pipe_root;

	if (*(int *)root == PIPE)
	{
		pipe_root = (t_pipe *)root;
		execute_tree_recur(shell, pipe_root->left, frk, pipe_index);
		if (*(int *)pipe_root->right == PIPE)
			execute_tree_recur(shell, pipe_root->right, frk, pipe_index + 1);
		else
			check_lastcmd(shell, pipe_root->right, frk, pipe_index + 1);
	}
	else if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
}
