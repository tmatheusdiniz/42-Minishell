/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:11:08 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/06 15:12:01 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	aux_clean_parsing(t_tokens *token_data, t_shell *mini, char **input_split)
{
	if (token_data)
		free_all_collected_tokens(token_data);
	mini->tokens = NULL;
	clean_matrix(input_split);
	g_define_sign(0);
	return (-1);
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
