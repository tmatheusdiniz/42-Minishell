/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/27 11:54:12 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"
#include "structs.h"
#include <minishell.h>

int	update_oldpwd(t_env_v *env_v)
{
	t_env_v	*oldpwd;
	t_env_v	*current_pwd;

	current_pwd = get_node_envp(env_v, "PWD");
	oldpwd = get_node_envp(env_v, "OLDPWD");
	if (current_pwd)
	{
		if (oldpwd)
		{
			free(oldpwd->value);
			oldpwd->value = ft_strdup(current_pwd->value);
			if (!oldpwd->value)
				return (1);
		}
	}
	return (0);
}

int	update_pwd(t_env_v *env_v)
{
	char	pwd[PATH_MAX];
	t_env_v	*pwd_node;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("pwd error:");
		return (1);
	}
	pwd_node = get_node_envp(env_v, "PWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(pwd);
		if (!pwd_node->value)
			return (2);
	}
	return (0);
}

void	change_dir(t_shell *shell, char *target)
{
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit_code(1);
	}
	else
	{
		if (update_oldpwd(shell->env_v))
			malloc_failure(shell, "change_dir");
		if (update_pwd(shell->env_v) == 1)
		{
			exit_code(1);
			return ;
		}
		else if (update_pwd(shell->env_v) == 2)
			malloc_failure(shell, "change_dir");
		exit_code(0);
	}
}

char	*get_target(t_env_v *env_v, char *input)
{
	t_env_v	*oldpwd;

	if (ft_strncmp(input, "-", ft_strlen(input)) == 0)
	{
		oldpwd = get_node_envp(env_v, "OLDPWD");
		if (oldpwd)
			return (oldpwd->value);
	}
	return (input);
}

void	ft_cd(t_shell *shell, t_exec *exec_node)
{
	char	*target;
	t_env_v	*home;

	home = get_node_envp(shell->env_v, "HOME");
	if (exec_node->argv[1] && exec_node->argv[2])
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else
	{
		if (!exec_node->argv[1])
		{
			if (!home || !home->value)
			{
				ft_putendl_fd("minishell: cd: HOME not set", 2);
				exit_code(1);
				return ;
			}
			else
				target = home->value;
		}
		else
			target = get_target(shell->env_v, exec_node->argv[1]);
		if (exec_node->argv[1] && ft_strncmp(exec_node->argv[1], "-", 2) == 0)
			ft_printf("%s\n", target);
		change_dir(shell, target);
	}
}
