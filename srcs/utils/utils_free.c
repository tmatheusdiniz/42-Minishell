/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:18:17 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/22 10:10:59 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_structs(t_shell *shell)
{
	if (shell)
	{
		if (shell->input)
			free(shell->input);
		if (shell->env_v)
			clean_env_v(shell->env_v);
		free(shell);
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

void	clean_env_v(t_env_v *env)
{
	t_env_v	*cur;

	if (!env)
		return ;
	cur = env;
	while (cur)
	{
		cur = env->next;
		free(env);
	}
}