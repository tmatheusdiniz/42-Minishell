/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:08:30 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/19 15:50:38 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_args(int argc, char const **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd(RED"Invalid input"DEFAULT, 2);
		exit(1);
	}
	if (!envp || !*envp)
		ft_putendl_fd(RED""DEFAULT, 2);
	return (0);
}

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		malloc_failure(shell, "init_shell");
	shell->input = NULL;
	shell->input_split = NULL;
	shell->envp = NULL;
	shell->env_v = NULL;
	return (shell);
}

void	handle_env_vars(t_shell *shell, char **envp)
{
	shell->env_v = envp_to_linked_l(envp);
	if (!shell->env_v)
		malloc_failure(shell, "handle_env_vars");
}
