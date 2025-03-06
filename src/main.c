/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/03 11:55:43 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_mini	*init_mini(int argc, char const **argv, char **envp)
{
	t_mini *mini;
	
	mini = ft_calloc(sizeof(t_mini), 1);
	if (!mini)
		mini_errors(mini, "Calloc: Calloc failed", 0);
	mini->args = argv;
	mini->env = env;
}

int main(int argc, char const **argv, char **envp)
{
	t_mini *mini;
	
	mini = init_data(argc, argv, env);

	exit_mini(mini, EXIT_FAILURE);
		
}
