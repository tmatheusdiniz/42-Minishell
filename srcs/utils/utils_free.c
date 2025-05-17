/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/08 19:03:10 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_structs(t_shell *shell)
{
<<<<<<< HEAD:srcs/utils/utils_free.c
	if (shell)
	{
		if (shell->input)
			free (shell->input);
		if (shell->env_v)
			// call function to clean env_v;
		free(shell);
	}
}

void	clean_matrix(char **matrix)
=======
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
>>>>>>> Parsing:srcs/utils/free.c
{
	int	i;

	i = 0;
<<<<<<< HEAD:srcs/utils/utils_free.c
	while (matrix[i])
		free(matrix[i++]);
	free (matrix);
=======
	while (token[i])
	{
		if (token[i]->token)
			free(token[i]->token);
		if (token[i])
			free(token[i]);
		i++;
	}
	if (token)
		free(token);
	return ;
>>>>>>> Parsing:srcs/utils/free.c
}
