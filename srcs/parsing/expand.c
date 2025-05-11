/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/10 23:46:26 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	in_quotes(char cur, int *i, bool flag)
{
	if (cur == '\'' && flag == true)
	{
		flag = false;
		(*i)++;
	}
	if (cur == '\'')
	{
		flag = true;
		(*i)++;	
	}
	return (flag);
}

char	*change_input(char *input, int *i, char *env, bool flag)
{
	char	string[999];
	int		j;

	j = -1;
	while (input[*i])
	{
		flag = in_quotes(input[*i], &(*i), flag);
		if (input[*i] == '$' && flag)
		{
			(*i)++;
			while (input[*i] && input[*i] != 32 && input[*i] != '\'')
				string[j++] = input[(*i)++];
			break ;
		}
		else if (input[*i] == '$' && !flag)
		{
			(*i)++;
			while (env[j++])
				string[j] = env[j];
			break ;
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
	bool	flag;

	flag = false;
	i = 0;
	if (!input || !mini)
		return (NULL);
	new_input = NULL;
	flag = in_quotes(input[i], &i, flag);
	index_env = get_index_env(mini, input);
	if (index_env != -1)
		new_input = change_input(input, &i,
				mini->env[index_env] + ft_strlen(input) + 1, flag);
	free(input);
	return (new_input);
}
