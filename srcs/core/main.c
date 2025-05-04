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
		return (NULL);
	mini->envp = duplicate_env_v(envp);
	mini->env_v = NULL;
	mini->input = NULL;
	return (mini);
}

t_env_v	*init_env_v(t_env_v *env_v, char **envp)
{
	env_v = envp_to_linked_l(envp);
	if (!env_v)
		return (NULL);
	ft_sort_linked(env_v);
	return (env_v);
}

int	main(int argc, char const **argv, char **envp)
{
	t_mini	*mini;
	char	**input_split;

	if (argc > 1)
		return (ft_printf("Minishell: %s: No such file or directory", argv[1]));
	mini = init_mini(envp);
	mini->env_v = init_env_v(mini->env_v, mini->envp);
	input_split = NULL;
	while (1)
	{
		signal_init();
		mini->input = readline("Minishell: ");
		if (!mini->input)
			handle_errors(mini, "exit", SIGQUIT, input_split);
		if (!*mini->input)
			continue;
		add_history(mini->input);
		input_split = ft_split(mini->input, ' ');
		input_split[0] = check_space(input_split[0]);
		if (check_command(mini, input_split) == -1)
			handle_errors(mini, "exit", SIGQUIT, input_split);
	}
}
