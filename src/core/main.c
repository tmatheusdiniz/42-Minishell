/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/23 14:32:41 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_mini	*init_mini(char **envp)
{
	t_mini *mini;
	
	mini = ft_calloc(sizeof(t_mini), 1);
	if (!mini)
		mini_errors(mini, "Calloc: Calloc failed", 0);
	mini->env = duplicate_env(envp);
	return(mini);
}

int main(int argc, char const **argv, char **envp)
{
	t_mini *mini;
	char *input;
	char **input_split;

	(void)argv;
	(void)argc;
	mini = init_mini(envp);
	while(1)
	{
		input = readline("Minishell: ");
		input_split = ft_split(input, ' ');
		input_split[0] = check_space(input_split[0]);
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
		else
			printf("Command '%s' not found\n", input_split[0]);
	}
}
