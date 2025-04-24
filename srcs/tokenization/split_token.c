/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:09:56 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/24 12:43:43 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	i_tokens(char *str)
{
	int		i;
	int		words;
	char	quotes;

	i = 0;
	words = 0;
	if (str[i])
		words = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				i++;
		}
		if (str[i] && str[i] == ' ' && str[i + 1])
			words++;
		if (str[i])
			i++;
	}
	return (words);
}

int	len_token(char *token)
{
	int		i;
	char	quotes;
	i = 0;
	while (token[i] && token[i] != ' ')
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			quotes = token[i++];
			while (token[i] && token[i] != quotes)
				i++;
		}
		if (token[i])
			i++;
	}
	return (i);	
}

static void	memfree(char **list, int count)
{
	while (count >= 0)
	{
		free(list[count]);
		count--;
	}
	free(list);
}

static char	*fill(char *str, int *start)
{
	int		token_len;
	char	*fill;
	
	if (str[*start] == ' ')
		(*start)++;
	token_len = len_token(&str[*start]);
	fill = ft_substr(str, *start, token_len);
	if (!fill)
		return (NULL);
	*start = *start + token_len;
	return (fill);
}

char	**split_token(char *str)
{
	char	**token_list;
	int		size_of_list;
	int		i;
	int		s;

	size_of_list = i_tokens(str);
	token_list = (char **)ft_calloc(sizeof(char *), (size_of_list + 1));
	if (!token_list)
		return (0);
	i = 0;
	s = 0;
	while (i < size_of_list)
	{
		token_list[i] = fill(str, &s);
		if (!token_list[i])
			return (memfree(token_list, i), NULL);
		i++;
	}
	token_list[i] = NULL;
	return (token_list);
}
