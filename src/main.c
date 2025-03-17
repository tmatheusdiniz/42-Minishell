/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/17 19:12:12 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_mini	*init_mini(char **envp)
{
	t_mini *mini;
	
	mini = ft_calloc(sizeof(t_mini), 1);
	if (!mini)
		mini_errors(mini, "Calloc: Calloc failed", 0);
	mini->env = envp;
	return(mini);
}

int main(int argc, char const **argv, char **envp)
{
	t_mini *mini;
	char *input;
	char **teste;

	(void)argv;
	(void)argc;
	mini = init_mini(envp);
	while(1)
	{
		input = readline("Minishell: ");
		teste = ft_split(input, ' ');
		if (!ft_strncmp(input, "cd", 2))
		{
			printf("Entrou no cd do main\n");
			cd(mini, teste);
		}
		if (!ft_strncmp(input, "pwd", 3))
			pwd();
		if (!ft_strncmp(input, "echo", 4))
		{
			printf("Entrou no echo do main\n");
			echo(input);
		}
	}
	//exit_mini(mini, EXIT_FAILURE);	
}
