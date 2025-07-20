/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:30:46 by alberto           #+#    #+#             */
/*   Updated: 2025/07/21 00:31:03 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static t_tokens	*init_token_data(int count)
{
	t_tokens	*data;

	data = malloc(sizeof(t_tokens));
	if (!data)
		return (NULL);
	data->tokens = malloc(sizeof(t_token *) * (count + 1));
	if (!data->tokens)
	{
		free(data);
		return (NULL);
	}
	data->count = count;
	return (data);
}

t_tokens	*collect_all_tokens(t_token *tokens)
{
	t_tokens	*data;
	t_token		*current;
	int			i;
	int			count;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	data = init_token_data(count);
	if (!data)
		return (NULL);
	current = tokens;
	i = 0;
	while (current && i < count)
	{
		data->tokens[i] = current;
		current = current->next;
		i++;
	}
	data->tokens[i] = NULL;
	return (data);
}

void	free_all_collected_tokens(t_tokens *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->tokens[i])
		{
			if (data->tokens[i]->token)
			{
				free(data->tokens[i]->token);
				data->tokens[i]->token = NULL;
			}
			free(data->tokens[i]);
			data->tokens[i] = NULL;
		}
		i++;
	}
	free(data->tokens);
	free(data);
}