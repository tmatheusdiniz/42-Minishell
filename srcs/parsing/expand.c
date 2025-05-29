/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/23 10:58:33 by alberto          ###   ########.fr       */
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

char	*change_expansible(t_shell *mini, char *input, int *i, char *string, int *j)
{
	char	*env_var;
	int		index_env;
	int		c;

	env_var = check_env_var(input, &*i);
	c = ft_strlen(env_var) + 1;
	index_env = get_index_env_parsing(mini, env_var);
	if (index_env != -1)
	{
		while (mini->envp[index_env][c])
		{
			string[*j] = mini->envp[index_env][c];
			(*j)++;
			c++;
		}
		free(env_var);
		return (string);
	}
	else
		return (NULL);
}

char	*change_input(t_shell *mini, char *input, int *i)
{
	char	string[999];
	int		j;

	j = 0;
	while (input[*i])
	{
		if (input[*i] == '$')
			change_expansible(mini, input, &*i, string, &j);
		else
		{
			string[j] = input[*i];
			j++;
			(*i)++;
		}
	}
	string[j] = '\0';
	return (ft_strdup(string));
}

char	*expand(char *input, t_shell *mini)
{
	char	*new_input;
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
		input = clean_quotes(input);
		new_input = change_input(mini, input, &i);
		if (!new_input)
			return (NULL);
	}
	return (new_input);
}
