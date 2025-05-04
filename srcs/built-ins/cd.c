/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 15:30:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(t_env_v *env_v)
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
				return ; //Handle this error after
		}
	}
}

void	update_pwd(t_env_v *env_v)
{
	t_env_v *pwd_node;
	char 	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("pwd error:");
		return ;
	}
	pwd_node = get_node_envp(env_v, "PWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(pwd);
		if (!pwd_node->value)
			return ;
	}
}

int	change_dir(t_env_v *env_v, char *target)
{
	if (chdir(target) != 0)
		ft_printf("Minishell: cd: %s: No such file or directory\n", target);
	else
	{
		update_oldpwd(env_v);
		update_pwd(env_v);
	}
	return (0);
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

int	cd(t_mini *mini, char **input)
{
	char	*target;
	t_env_v	*home;

	home = get_node_envp(mini->env_v, "HOME");
	if (input[2])
		printf("Minishell: cd: too many arguments\n");
	else
	{
		if (!input[1])
		{
			if (!(home->value))
				return (error_message("Minishell: cd: HOME not set", 2), 0);
			else
				target =  home->value;
		}
		else
			target = get_target(mini->env_v, input[1]);
		if (input[1] && ft_strncmp(input[1], "-", 2) == 0)
			ft_printf("%s\n", target);
		change_dir(mini->env_v, target);
	}
	return (0);
}
