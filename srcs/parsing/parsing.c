/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:35:25 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/24 12:43:24 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parsing(char *input)
{
	char	**input_split;

	input_split = split_token(input);
	return (input_split);
}

void	cmds(char **input_split, t_mini *mini)
{
	if (!ft_strncmp(input_split[0], "cd", ft_strlen(input_split[0])))
		cd(mini, input_split);
	else if (!ft_strncmp(input_split[0], "pwd", ft_strlen(input_split[0])))
		pwd();
	else if (!ft_strncmp(input_split[0], "echo", ft_strlen(input_split[0])))
		echo(input_split);
	else if (!ft_strncmp(input_split[0], "env", ft_strlen(input_split[0])))
	{
		if (input_split[1])
			printf("env: '%s': No such file or directory\n", input_split[1]);
		else
			env(mini->env);
	}
	else if (!ft_strncmp(input_split[0], "unset", ft_strlen(input_split[0])))
		unset(mini, input_split[1]);
	else
		printf("Command '%s' not found\n", input_split[0]);
}
