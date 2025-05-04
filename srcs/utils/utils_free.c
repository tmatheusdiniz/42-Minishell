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

void	free_structs(t_mini *mini)
{
	if (mini)
	{
		if (mini->input)
			free (mini->input);
		if (mini->env_v)
			// call function to clean env_v
		free(mini);
	}
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free (matrix);
}
