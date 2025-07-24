/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:08:03 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/24 19:15:17 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>

static int	check_if_relative_path(t_exec *exec_node, char *command);

static char	*find_path(char **env_var)
{
	while (*env_var)
	{
		if (!ft_strncmp(*env_var, "PATH=", 5))
			return (*env_var + 5);
		env_var ++;
	}
	return (NULL);
}

static int	check_if_relative_path(t_exec *exec_node, char *command)
{
	if (access(command, X_OK) == 0)
		return (exec_node->cmd_path = command, 1);
	else
		return (0);
}

int	find_executable(t_shell *shell, t_exec *exec_node, char *command)
{
	int		i;
	char	*path;
	char	*temp_path;
	char	**directories;

	i = 0;
	if (check_if_relative_path(exec_node, command))
		return (0);
	path = find_path(shell->envp);
	if (!path)
		return (-1);
	directories = ft_split(path, ':');
	if (!directories)
		malloc_failure(shell, "find_bin");
	while (directories[i])
	{
		temp_path = ft_strjoin(directories[i], "/");
		path = ft_strjoin(temp_path, command);
		free (temp_path);
		if (access(path, X_OK) == 0)
			return (clean_matrix(directories), exec_node->cmd_path = path, 0);
		free (path);
		++ i;
	}
	return (clean_matrix(directories), -1);
}

void	check_lastcmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index)
{
	if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
	else if (*(int *)root == OUTREDIR)
		exec_outredir(shell, shell->root);
	else if (*(int *)root == INREDIR)
		exec_inredir(shell, shell->root);
	else if (*(int *)root == APPEND)
		exec_append(shell, root);
	else if (*(int *)root == HEREDOC)
		exec_heredoc(shell, root);
}
