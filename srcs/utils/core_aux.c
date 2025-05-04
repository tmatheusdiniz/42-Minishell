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

#include "../../include/minishell.h"

int	check_command(t_mini *mini, char **input)
{
	if (!ft_strncmp(input[0], "cd", ft_strlen(input[0])))
		cd(mini, input);
	else if (!ft_strncmp(input[0], "pwd", ft_strlen(input[0])))
		pwd();
	else if (!ft_strncmp(input[0], "echo", ft_strlen(input[0])))
		echo(input);
	else if (!ft_strncmp(input[0], "env", ft_strlen(input[0])))
	{
		if (input[1])
		{
			printf("env: '%s': No such file or directory\n", input[1]);
			return (-1);
		}
		else
			env(mini->envp);
	}
	else if (!ft_strncmp(input[0], "unset", ft_strlen(input[0])))
		unset(mini, input[1]);
	else if (!(ft_strncmp(input[0], "export", ft_strlen(input[0]))))
		export_func(mini, input[1]);
	else
		printf("Command '%s' not found\n", input[0]);
	return (0);
}
