/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/20 16:26:55 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mini(t_mini *mini, char *message, int errnbr, char **input_split)
{
	if (mini)
	{
		ft_free_split(mini->env);
		free(mini);
	}
	if (input_split)
		ft_free_split(input_split);
	error_message(message, 2);
	exit(errnbr);
}
void	free_token(t_token **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if(token[i]->token)
			free(token[i]->token);
		if (token[i])
			free(token[i]);
		i++;
	}
	if (token)
		free(token);
	return ;
}