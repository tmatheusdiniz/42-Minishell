/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:35:25 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/08 20:14:58 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_dollar(char *input)
{
	int	i;
	int	flag;
	int	pid;

	flag = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] && (input[i] == '$' && flag == 1))
		{
			pid = getpid();
			ft_putnbr_fd(pid, 1);
			flag = 0;
		}
		if (input[i] && input[i] == '$')
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (true);
	return (false);
}

bool	check_quotes(char *input_split, char quotes)
{
	int	i;
	int	flag_quotes;

	flag_quotes = 0;
	i = 0;
	while (input_split[i])
	{
		if (input_split[i] && (input_split[i] == quotes && flag_quotes == 1))
		{
			flag_quotes = 0;
			i++;
		}
		if (input_split[i] && input_split[i] == quotes)
			flag_quotes = 1;
		i++;
	}
	if (flag_quotes == 1)
		return (false);
	return (true);
}

char	**parsing(char *input, t_mini *mini)
{
	char	**input_split;
	int		i;

	i = 0;
	input_split = split_token(input);
	while (input_split[i])
	{
		if (!check_quotes(input_split[i], '"')
			|| !check_quotes(input_split[i], '\''))
		{
			print_error(NAME_SHELL,
				"syntax error - the quote is open", NULL, NULL);
			return (NULL);
		}
		if (check_dollar(input_split[i]))
			input_split[i] = expand(input_split[i], mini);
		i++;
	}
	free(input);
	return (input_split);
}

void	cmds(char **input_split, t_mini *mini)
{
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
	else if (!ft_strncmp(input_split[0], "unset", ft_strlen(input_split[0])))
		unset(mini, input_split[1]);
	else
		printf("Command '%s' not found\n", input_split[0]);
}
