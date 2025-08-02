/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:54 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/29 18:52:48 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	handle_metachar(const char *input, char *new_str, int *i, int *j)
{
	if (*j > 0 && new_str[*j - 1] != ' ')
		new_str[(*j)++] = ' ';
	new_str[(*j)++] = input[*i];
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		new_str[(*j)++] = input[*i];
		(*i)++;
	}
	if (input[*i + 1] && input[*i + 1] != ' ')
		new_str[(*j)++] = ' ';
}

char	*add_spaces_around_metachars(const char *input)
{
	char	*new_str;
	int		i;
	int		j;
	char	quotes;

	i = 0;
	j = 0;
	quotes = 0;
	new_str = ft_calloc(ft_strlen(input) * 3 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (input && input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quotes == 0)
			quotes = input[i];
		else if (input[i] == quotes)
			quotes = 0;
		if (is_metachar(input[i]) && !quotes)
			handle_metachar(input, new_str, &i, &j);
		else
			new_str[j++] = input[i];
		i++;
	}
	return (new_str);
}

bool	valid_arguments(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if ((input[i] == '>' || input[i] == '<')
				&& input[i + 1] == input[i])
			{
				i++;
				if (input[i] && input[i + 1] == 0)
					return (false);
			}
			if (input[i] && input[i + 1] == 0)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	input_validation(t_shell *shell)
{
	char	*trimmed_input;
	char	*spaced_input;

	if (!shell->input || !shell->input[0])
		return (true);
	trimmed_input = ft_strtrim(shell->input, "\t ");
	if (!valid_arguments(trimmed_input))
	{
		print_error(NAME_SHELL,
			": syntax error near unexpected token `newline'", NULL, NULL);
		return (free(trimmed_input), true);
	}
	free(shell->input);
	spaced_input = add_spaces_around_metachars(trimmed_input);
	free(trimmed_input);
	shell->input = spaced_input;
	if (!shell->input)
		return (exit_code(2));
	if (check_quotes(shell->input, '"')
		|| check_quotes(shell->input, '\''))
		return (print_error(NAME_SHELL,
				"syntax error - unclosed quotes", NULL, NULL), exit_code(2));
	return (false);
}
