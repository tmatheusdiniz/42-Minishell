/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:07:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/20 22:49:59 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*create_new_token(char *input, int index)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(input);
	new->index = index;
	new->type = match_type(input);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void	add_token_to_list(t_shell *mini, t_token *new_token)
{
	t_token	*cur;

	if (!mini->tokens)
	{
		mini->tokens = new_token;
		return ;
	}
	cur = mini->tokens;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new_token;
	new_token->prev = cur;
}

void	create_token_list(char **input_split, t_shell *mini, int i)
{
	t_token	*new_token;
	int		token_index;

	if (!input_split || !*input_split)
		return ;
	token_index = 0;
	while (input_split[i])
	{
		if (input_split[i] && *input_split[i])
		{
			new_token = create_new_token(input_split[i], token_index);
			if (!new_token)
				return ;
			add_token_to_list(mini, new_token);
			token_index++;
		}
		i++;
	}
}
