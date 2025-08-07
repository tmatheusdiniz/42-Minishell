/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:22:29 by alberto           #+#    #+#             */
/*   Updated: 2025/08/06 23:07:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**prepare_argv_for_exec(char **argv)
{
	char	**clean_argv;
	int		i;
	int		count;
	int		len;

	i = 0;
	count = 0;
	while (argv[count])
		count++;
	clean_argv = ft_calloc(sizeof(char *), count + 1);
	if (!clean_argv)
		return (NULL);
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		if (len >= 2
			&& ((argv[i][0] == '\'' && argv[i][len - 1] == '\'')
				|| (argv[i][0] == '"' && argv[i][len - 1] == '"')))
			clean_argv[i] = ft_substr(argv[i], 1, len - 2);
		else
			clean_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	clean_argv[i] = NULL;
	return (clean_argv);
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
		return (false);
	}
	return (true);
}
