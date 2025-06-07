/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:35:25 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/06 23:37:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_dollar(char *input)
{
	int		i;
	bool	flag;
	int		pid;

	flag = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			flag = true;
			if (input[i + 1] == '$' && flag)
			{
				pid = getpid();
				ft_putnbr_fd(pid, 1);
				flag = false;
			}
		}
		i++;
	}
	return (flag);
}

bool	check_quotes(char *input_split, char quotes)
{
	int		i;
	bool	flag_quotes;

	i = 0;
	flag_quotes = false;
	while (input_split[i])
	{
		if (input_split[i] == quotes)
		{
			if (flag_quotes)
				flag_quotes = false;
			else
				flag_quotes = true;
		}
		i++;
	}
	return (flag_quotes);
}

char	**make_process(char **input_split, t_shell *mini)
{
	int		i;

	i = 0;
	while (input_split[i])
	{
		if (check_quotes(input_split[0], '"')
			|| check_quotes(input_split[0], '\''))
			input_split[0] = clean_quotes(input_split[0], 0 , 0);
		if (check_dollar(input_split[i]))
			input_split[i] = expand(input_split[i], mini);
		else
			input_split[i] = clean_quotes(input_split[i], 0 , 0 );
		i++;
	}
	return (input_split);
}

char	**parsing(char *input, t_shell *mini)
{
	char	**input_split;
	
	input = check_space(input);
	input_split = split_token(input);
	input_split = make_process(input_split, mini);
	create_token_list(input_split, mini, 0);
	mini->root = build_tree(mini->tokens);
	if (check_command(mini, input_split) == -1)
		handle_errors(mini, "exit", SIGQUIT, input_split);
	return (input_split);
}
