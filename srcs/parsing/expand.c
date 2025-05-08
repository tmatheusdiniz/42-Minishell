/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/06 11:56:50 by alberto          ###   ########.fr       */
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

char	*change_input(char *input, char	*env)
{
	char	string[999];
	bool	flag;
	int		i;
	int 	j;

	flag = false;
	j = 0;
	while (input[i])
	{
		flag = in_quotes(input[i], &i, flag);
		if (input[i] == '$' && flag)
		{
			i++;
			while (input[i] != 32)
				string[j++] = input[i++];
		}
		else if (input[i] == '$' && !flag)
		{
			i++;
			while (input[i] != 32)
				string[j++] = env[i++];
		}
	}
	string[j] = '\0';
	return (ft_strdup(string));
}

char	*expand(char *input, t_mini *mini)
{
	char	*new_input;
	int		index_env;

	if (!input || !mini)
		return (NULL);
	new_input = NULL;
	index_env = get_index_env(mini, &input[1]);
	if (index_env != -1)
		new_input = change_input(input, mini->env[index_env] + ft_strlen(input) + 1);
	free(input);
	return(new_input);
}
