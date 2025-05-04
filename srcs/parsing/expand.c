/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/04 16:43:24 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



char	*change_input(char *input, int index_env, t_mini *mini)
{
	char string[999];
	int in_quote;
	char *env;
	int	i;
	int j;

	env = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
			in_quote = 1;
		if (input[i] == '$' && !in_quote)
		{
			i++;
			j = 0;
			while (str[i] != 32)
			{
				env[j++] = str[i++];
			}
		}
		string[i] = str[i];
		i++;
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
	index_env = get_index_env(mini, input);
	if (index_env != -1)
		new_input = change_input(input, index_env, mini);
	free(input);
	return(new_input);
}
