/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/23 00:07:32 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	int	indexoldpwd;

	indexoldpwd = get_index_env(mini, "OLDPWD");
	if (indexoldpwd != -1)
	{
		oldpwd = mini->env[get_index_env(mini, "PWD")] + (ft_strlen("PWD") + 1);
		if (oldpwd)
		{
			free(mini->env[indexoldpwd]);
			mini->env[indexoldpwd] = (char *)malloc(sizeof(char) * (ft_strlen(oldpwd) + 1));
			if (!mini->env[indexoldpwd])
			mini_errors(mini, "Malloc Error: update oldpwd", 1);
			ft_strncpy(mini->env[indexoldpwd], oldpwd, ft_strlen(oldpwd));
		}
	}
}


void	update_pwd(t_mini *mini)
{
	char	*pwd;
	int	indexpwd;

	indexpwd = get_index_env(mini, "PWD");
	if (indexpwd != -1)
	{
		pwd = getenv("PWD");
		free(mini->env[indexpwd]);
		mini->env[indexpwd] = (char *)malloc(sizeof(char) * ft_strlen(pwd) + 1);
		if (!mini->env[indexpwd])
			mini_errors(mini, "Malloc Error: update pwd", 1);
		ft_strncpy(mini->env[indexpwd], pwd, ft_strlen(pwd));
	}
}

int	change_dir(t_mini *mini, char *target)
{
	printf("chegou no change_dir com esse target -> %s\n", target);
	if (!target)
		mini_errors(mini, "Minishell: cd: HOME not set", 1);
	if (chdir(target) != 0)
		mini_errors(mini, "cd deu errado aqui no chdir", 1);
	update_oldpwd(mini);
	update_pwd(mini);
	return (0);
}

char	*get_target(char *input, t_mini *mini)
{
	printf("chegou no get_target\n");
	if (!input)
	{
		printf("return home: %s\n", getenv("HOME"));
		return (getenv("HOME"));
	}
	if (ft_strncmp(input, "-", ft_strlen(input)) == 0)
		return (mini->env[get_index_env(mini, "OLDPWD")] + 7);
	return (input);
}

int	cd(t_mini *mini, char **input)
{
	char	*target;
	
	printf("input[0] no cd -> %s\n", input[0]);
	printf("input[1] no cd -> %s\n", input[1]);
/* 	if (input[2])
	{
		printf("vai dar erro de too many arguments por isso: -> %s\n", input[2]);	
		mini_errors(mini, "Minishell: cd: too many arguments", 1);
	} */
	target = get_target(input[1], mini);
	if (!target)
		mini_errors(mini, "sem target no cd", 1);
	printf("return do get_target no cd: %s\n", target);
	if (input[1] && ft_strncmp(input[1], "-", 2) == 0)
		printf("id dentro do cd : %s\n", target);
	change_dir(mini, target);
	return (0);
}
