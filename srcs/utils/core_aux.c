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

int	check_args(int argc, char **envp)
{
	if (argc > 1)
	{
		ft_putendl_fd(RED"Invalid input"DEFAULT, 2);
		exit(1);
	}
	if (!envp || !*envp)
		ft_putendl_fd(RED""DEFAULT, 2);
	return (0);
}

int	check_command(t_shell *shell, char **input)
{
	if (!ft_strncmp(input[0], "cd", ft_strlen(input[0])))
		ft_cd(shell->env_v, input);
	else if (!ft_strncmp(input[0], "pwd", ft_strlen(input[0])))
		ft_pwd();
	else if (!ft_strncmp(input[0], "echo", ft_strlen(input[0])))
		ft_echo(input);
	else if (!ft_strncmp(input[0], "env", ft_strlen(input[0])))
	{
		if (input[1])
		{
			ft_printf("env: '%s': No such file or directory\n", input[1]);
			return (-1);
		}
		else
			ft_env(shell->envp);
	}
	else if (!ft_strncmp(input[0], "unset", ft_strlen(input[0])))
		ft_unset(shell->env_v, input[1]);
	else if (!(ft_strncmp(input[0], "export", ft_strlen(input[0]))))
		ft_export(shell->env_v, input[1]);
	else
		ft_printf("%s: command not found\n", input[0]);
	return (0);
}
