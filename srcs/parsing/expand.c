/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/29 19:05:13 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	in_quotes(char cur, int *i, bool flag, int quotes, bool inc)
{
	if (cur == quotes && flag && inc)
	{
		flag = false;
		(*i)++;
	}
	if (cur == quotes && inc)
	{
		flag = true;
		(*i)++;
	}
	if (cur == quotes && flag && !inc)
	{
		flag = false;
		return (flag);
	}
	if (cur == quotes && !inc)
		flag = true;
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
	bool	d_flag;
	bool	s_flag;

	j = 0;
	d_flag = false;
	s_flag = false;
	while (input[*i])
	{
		d_flag = in_quotes(input[*i], &*i, d_flag, '"', false);
		s_flag = in_quotes(input[*i], &*i, s_flag, '\'', false);
		if (input[*i] == '$' && ((d_flag && s_flag) || (!d_flag && !s_flag)
					|| (d_flag && !s_flag)))
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
	//bool	s_flag; seted but not used

	//s_flag = false;
	i = 0;
	if (!input || !mini)
		return (NULL);
	new_input = change_input(mini, input, &i);
	if (!new_input)
		return (NULL);
	new_input = clean_quotes(new_input, 0, 0);
	return (new_input);
}
