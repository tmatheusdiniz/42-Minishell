/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/21 18:15:16 by cda-fons         ###   ########.fr       */
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

void	change_expansible(t_shell *mini, char *input, int *i, char *string, int *j)
{
	char	*env_var;
	int		index_env;
	int		c;

	env_var = check_env_var(input, &*i);
	c = ft_strlen(env_var);
	index_env = get_index_env_parsing(mini, env_var);
	if (index_env != -1)
	{
		while (mini->envp[index_env])
			string[(*j)++] = mini->envp[index_env][c++];
		return ;
	}
	else
		return ;
	
}

char	*change_input(t_shell *mini, char *input, int *i, bool s_flag)
{
	char	string[999];
	int		j;

	j = 0;
	while (input[*i])
	{
		s_flag = in_quotes(input[*i], &*i, s_flag, '\'');
		if (input[*i] == '$' || !s_flag)
			change_expansible(mini, &input[*i], &*i, &string[j], &j);
		if (input[*i] == '$' || s_flag)
			string[j++] = input[(*i)++];
		else
			string[j++] = input[(*i)++];
			
	}
	string[j] = '\0';
	return (ft_strdup(string));
}

void ft_free(char **s)
{
	if (!s || !(*s))
		return ;
	free (*s);
	*s = NULL;
}

char	*expand(char *input, t_shell *mini)
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
		index_env = get_index_env_parsing(mini, input);
		input = clean_quotes(input);
		if (index_env != -1)
		{
			new_input = change_input(mini, input, &i, s_flag);
			if (!new_input)
				return (NULL);
		}
	}
	return (new_input);
}
