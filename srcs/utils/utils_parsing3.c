/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:18:42 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/07 22:48:25 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_especial_caracters(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '$')
				return (true);
			if (input[i] == '_' || ((input[i] >= 'A' && input[i] <= 'Z')
					|| (input[i] >= 'a' && input[i] <= 'z')))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	check_closed_quotes(char *input_split, char quotes)
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

bool	check_heredoc_signal_on_input(char *input)
{
	int		i;
	bool	result;

	i = 0;
	result = false;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (input[i + 1] == input[i])
				result = true;
		}
		i++;
	}
	return (result);
}

bool	only_pipe_validations(char *input)
{
	if (input[0] == '|')
	{
		print_error(NAME_SHELL,
			": syntax error near unexpected token `|'", NULL, NULL);
		exit_code(2);
		return (false);
	}
	return (true);
}
