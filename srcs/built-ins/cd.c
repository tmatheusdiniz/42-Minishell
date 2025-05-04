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

void	update_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	int		indexoldpwd;

	indexoldpwd = get_index_env(mini, "OLDPWD");
	if (indexoldpwd != -1)
	{
		oldpwd = mini->envp[get_index_env(mini, "PWD")] + 4;
		if (oldpwd)
		{
			free(mini->envp[indexoldpwd]);
			printf("no oldpwd esta assim ->%s\n", mini->envp[indexoldpwd]);
			mini->envp[indexoldpwd] = ft_calloc(sizeof(char),
					(ft_strlen("OLDPWD=") + ft_strlen(oldpwd) + 1));
			if (!mini->envp[indexoldpwd])
				mini_errors(mini, "Malloc Error: update oldpwd", 1);
			ft_strcpy(mini->envp[indexoldpwd], "OLDPWD=");
			ft_strcat(mini->envp[indexoldpwd], oldpwd);
		}
	}
}

void	update_pwd(t_mini *mini)
{
	char	pwd[PATH_MAX];
	int		indexpwd;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("pwd error:");
		return ;
	}
	indexpwd = get_index_env(mini, "PWD");
	if (indexpwd != -1)
	{
		free(mini->envp[indexpwd]);
		mini->envp[indexpwd] = ft_calloc(sizeof(char),
				(ft_strlen("PWD=") + ft_strlen(pwd) + 1));
		if (!mini->envp[indexpwd])
			free_mini(mini, "Malloc Error: update pwd", 1, NULL);
		ft_strcpy(mini->envp[indexpwd], "PWD=");
		ft_strcat(mini->envp[indexpwd], pwd);
	}
}

int	change_dir(t_mini *mini, char *target)
{
	if (chdir(target) != 0)
		printf("Minishell: cd: %s: No such file or directory\n", target);
	else
	{
		update_oldpwd(mini);
		update_pwd(mini);
	}
	return (0);
}

char	*get_target(char *input, t_mini *mini)
{
	if (ft_strncmp(input, "-", ft_strlen(input)) == 0)
		return (mini->envp[get_index_env(mini, "OLDPWD")] + 7);
	return (input);
}

int	cd(t_mini *mini, char **input)
{
	char	*target;

	if (input[2])
		printf("Minishell: cd: too many arguments\n");
	else
	{
		if (!input[1])
		{
			if (get_index_env(mini, "HOME") == -1)
			{
				error_message("Minishell: cd: HOME not set", 2);
				return (0);	
			}
			else
				target =  mini->envp[get_index_env(mini, "HOME")] + 5;
		}
		else
			target = get_target(input[1], mini);
		if (input[1] && ft_strncmp(input[1], "-", 2) == 0)
			printf("%s\n", target);
		change_dir(mini, target);
	}
	return (0);
}
