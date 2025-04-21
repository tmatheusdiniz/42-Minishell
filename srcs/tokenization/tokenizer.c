/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:07:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/21 19:17:33 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* char	**tokenizer(char *input)
{
	
} */

int	create_token_list(char **input_split, t_mini *mini)
{
	int	i;

	i = 0;
	while (input_split[i])
	{
		
		t_token	*new;

		new = (t_token *)ft_calloc(1, sizeof(t_token));
		if (new.)
		{
			free_token(mini->tokens);
			ft_putstr_fd("Malloc error\n", 2);
			return (1);
		}
		mini->tokens[i]->type = match_type(input_split[i]);
		i++;
	}
	return (0);
}