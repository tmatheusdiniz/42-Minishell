/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/08 20:28:41 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	in_quotes(char cur, int *i, bool flag)
{
	if (cur == '\'' && flag == true)
		flag = false;
	if (cur == '\'')
		flag = true;
	if (flag)
		(*i)++;
	return (flag);
}

char	*change_input(char *input, int *i, char *env)
{
	char	string[999];
	int		j;
	bool	flag;

	flag = false;
	j = -1;
	while (input[*i])
	{
		flag = in_quotes(input[*i], &(*i), flag);
		if (input[*i] == '$' && flag)
		{
			(*i)++;
			while (input[*i] && input[*i] != 32)
				string[j++] = input[(*i)++];
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

	i = 0;
	if (!input || !mini)
		return (NULL);
	new_input = NULL;
	index_env = get_index_env(mini, &input[1]);
	if (index_env != -1)
		new_input = change_input(input, &i,
				mini->env[index_env] + ft_strlen(input));
	free(input);
	return (new_input);
}
