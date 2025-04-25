/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 13:24:34 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_mini	*init_mini(char **envp)
{
	t_mini	*mini;

	mini = ft_calloc(sizeof(t_mini), 0);
	if (!mini)
		mini_errors(mini, "Calloc: Calloc failed", 0);
	mini->env = duplicate_env(envp);
	return (mini);
}

int	main(int argc, char const **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	char	**input_split;

	(void)argv;
	if (argc > 1)
		return (ft_printf("you may use only one argument ... ./bin/minishell")); // temp handle
	mini = init_mini(envp);
	input = NULL;
	while (1)
	{
		signal_init();
		input = readline("Minishell: ");
		if (!input)
		{
			free_mini(mini, "exit", SIGQUIT, input_split);
			break ;
		}
		if (!*input)
			continue;
		add_history(input);
		input_split = ft_split(input, ' ');
		input_split[0] = check_space(input_split[0]);
		if (check_ifis_bt(mini, input_split) == -1)
			break; // temporary, after add other handle for it
	}
}
