/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/20 18:58:09 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	in_quotes(char cur, int *i, bool flag, int quotes)
{
	if (cur == quotes && flag == true)
	{
		flag = false;
		(*i)++;
	}
	if (cur == quotes)
	{
		flag = true;
		(*i)++;
	}
	return (flag);
}

char	*change_input(char *input, int *i, char *env)
{
	char	string[999];
	int		j;

	j = 0;
	while (input[*i])
	{
		if (env)
		{
			while (env[j])
			{
			string[j] = env[j];
			j++;
			}
		}
	}
	string[j] = '\0';
	return (ft_strdup(string));
}

char	*expand(char *input, t_mini *mini)
{
	char	*new_input;
	int		index_env;
	int		i;
	bool	s_flag;

	s_flag = false;
	i = 0;
	if (!input || !mini)
		return (NULL);
	new_input = NULL;
	s_flag = in_quotes(input[i], &i, s_flag, '\'');
	if (s_flag)
		new_input = clean_quotes(input);
	else
	{
		index_env = get_index_env_parsing(shell, input);
		input = clean_other_chars(input);
		if (index_env != -1)
			new_input = change_input(input, &i,
					mini->env[index_env] + ft_strlen(input) + 1);
	}
	return (ft_strdup(new_input));
}
