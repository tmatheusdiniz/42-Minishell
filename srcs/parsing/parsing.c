/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:35:25 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/27 11:40:34 by alberto          ###   ########.fr       */
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
	char	*temp;

	i = 0;
	while (input_split[i])
	{
		if (check_quotes(input_split[0], '"')
			|| check_quotes(input_split[0], '\''))
			input_split[0] = clean_quotes(input_split[0], 0, 0);
		if (check_dollar(input_split[i]))
		{
			temp = expand(input_split[i], mini);
			if (!temp)
				return (NULL);
			free(input_split[i]);
			input_split[i] = temp;
		}
		i++;
	}
	return (input_split);
}

int	parsing(t_shell *mini)
{
	char		**input_split;
	t_tokens	*token_data;

	input_split = split_token(mini->input);
	if (!input_split)
		return (-1);
	if (make_process(input_split, mini) == NULL)
		return (clean_matrix(input_split), -1);
	create_token_list(input_split, mini, 0);
	token_data = collect_all_tokens(mini->tokens);
	if (!token_data && mini->tokens)
		return (clean_matrix(input_split), -1);
	if (mini->tokens)
		mini->root = build_tree(mini->tokens);
	mini->original_root = mini->root;
	read_all_heredocs_with_shell(mini->root, mini);
	if (token_data)
		free_all_collected_tokens(token_data);
	mini->tokens = NULL;
	clean_matrix(input_split);
	if (!mini->root)
		return (-1);
	return (0);
}
