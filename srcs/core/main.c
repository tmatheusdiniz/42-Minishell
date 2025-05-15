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
#include "../../include/builtins.h"
#include "../../include/structs.h"
#include "../../include/utils.h"
#include "../../include/errors.h"
#include "../../include/signals.h"
#include <readline/readline.h>
#include <readline/history.h>

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 0);
	if (!shell)
		return (NULL);
	shell->envp = duplicate_env_v(envp);
	shell->env_v = NULL;
	shell->input = NULL;
	return (shell);
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
	t_shell	*shell;
	char	**input_split;

	if (argc > 1)
		return (ft_printf("Minishell: %s: No such file or directory", argv[1]));
	shell = init_shell(envp);
	shell->env_v = init_env_v(shell->env_v, shell->envp);
	input_split = NULL;
	while (1)
	{
		signal_init();
		shell->input = readline("Minishell: ");
		if (!shell->input)
			handle_errors(shell, "exit", SIGQUIT, input_split);
		if (!*shell->input)
			continue;
		add_history(shell->input);
		input_split = ft_split(shell->input, ' ');
		input_split[0] = check_space(input_split[0]);
		if (check_command(shell, input_split) == -1)
			handle_errors(shell, "exit", SIGQUIT, input_split);
	}
}
