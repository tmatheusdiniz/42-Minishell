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

static void	update_shlv(t_env_v *env_v);

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
	shell->cwd = NULL;
	shell->input_split = NULL;
	shell->envp = NULL;
	shell->env_v = NULL;
	shell->root = NULL;
	shell->tokens = NULL;
	return (shell);
}

static void	update_shlv(t_env_v *env_v)
{
	int		value;
	char	*value_str;
	t_env_v	*aux;

	aux = env_v;
	while (aux)
	{
		if (!strcmp(aux->key, "SHLVL"))
		{
			value = ft_atoi(aux->value);
			++value;
			value_str = ft_itoa(value);
			free (aux->value);
			aux->value = value_str;
		}
		aux = aux->next;
	}
}

void	handle_env_vars(t_shell *shell, char **envp)
{
	shell->env_v = envp_to_linked_l(envp);
	if (!shell->env_v)
		malloc_failure(shell, "handle_env_vars");
	update_shlv(shell->env_v);
	shell->envp = linked_to_envp(shell);
	if (!shell->envp)
		malloc_failure(shell, "handle_env_vars");
}
