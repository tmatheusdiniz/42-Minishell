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
static int	aux_find_executable(t_shell *shell, t_exec *exec_node,
				char *command, char **path);

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

static int	validate_file_type(char *command)
{
	struct stat	file_stat;

	if (stat(command, &file_stat) == -1)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
		return (-2);
	if (!S_ISREG(file_stat.st_mode))
		return (-3);
	return (0);
}

static int	check_if_relative_path(t_exec *exec_node, char *command)
{
	int	validation;

	if (!ft_strchr(command, '/'))
		return (0);
	validation = validate_file_type(command);
	if (validation == -2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		return (ft_putendl_fd(": Is a directory", 2), 126);
	}
	if (validation == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	if (validation == -3 || access(command, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		return (ft_putendl_fd(": Permission denied", 2), 126);
	}
	return (exec_node->cmd_path = ft_strdup(command), 1);
}

static int	aux_find_executable(t_shell *shell, t_exec *exec_node,
		char *command, char **path)
{
	int		path_check;

	path_check = check_if_relative_path(exec_node, command);
	if (path_check == 1)
		return (0);
	if (path_check > 1)
		return (path_check);
	*path = find_path(shell->envp);
	if (!path)
		return (127);
	return (-1);
}

int	find_executable(t_shell *shell, t_exec *exec_node, char *command)
{
	int		i;
	char	*path;
	char	*temp_path;
	char	**directories;

	path = NULL;
	i = aux_find_executable(shell, exec_node, command, &path);
	if (i >= 1)
		return (i);
	i = 0;
	directories = ft_split(path, ':');
	if (!directories)
		malloc_failure(shell, "find_bin");
	while (directories[i])
	{
		temp_path = ft_strjoin(directories[i++], "/");
		path = ft_strjoin(temp_path, command);
		free (temp_path);
		if (access(path, X_OK) == 0)
			return (clean_matrix(directories),
				exec_node->cmd_path = path, 0);
		free (path);
	}
	return (clean_matrix(directories), 127);
}
