/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 15:08:19 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//  Memory management will be done here.

void	free_mini(t_mini *mini, char *message, int errnbr, char **input_split)
{
    if (mini)
    {
        //ft_free_split(mini->env);
        free(mini);
    }
    if (input_split)
    {
        //ft_free_split(input_split);
    }
	error_message(message, 2);
    exit(errnbr);
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free (matrix);
}
