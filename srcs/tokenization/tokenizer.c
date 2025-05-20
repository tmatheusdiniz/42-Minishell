/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:07:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/20 15:27:31 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* char	**tokenizer(char *input)
{
	
} */

void	create_token_list(char **input_split, t_mini *mini, int i)
{
	t_token	*new;
	t_token	*cur;

	if (!input_split || !*input_split)
		return ;
	while (input_split[i])
	{
		new = (t_token *)ft_calloc(1, sizeof(t_token));
		ft_memset(new, 0, sizeof(new));
		new->token = ft_strdup(input_split[i]);
		new->index = i;
		if (i == 0)
			mini->tokens = new;
		else if (new->index > 0)
		{
			cur = mini->tokens;
			while (cur && cur->next)
				cur = cur->next;
			cur->next = new;
			new->prev = cur;
		}
		new->type = match_type(input_split[i]);
		i++;
	}
}
