/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:01:08 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/28 20:01:17 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_pipe(t_fork *frk, int pipe_index)
{
	int	i;

	i = 0;
	while (i < frk->nbr_cmds - 1)
	{
		if (i != pipe_index - 1)
			close (frk->pipe[i][0]);
		if (i != pipe_index)
			close (frk->pipe[i][1]);
		i ++;
	}
	if (pipe_index > 0)
	{
		dup2(frk->pipe[pipe_index - 1][0], STDIN_FILENO);
		close(frk->pipe[pipe_index - 1][0]);
	}
	if (pipe_index < frk->nbr_cmds - 1)
	{
		dup2(frk->pipe[pipe_index][1], STDOUT_FILENO);
		close(frk->pipe[pipe_index][1]);
	}
}

bool	check_pipe_rgt(void	*root)
{
	int	*type_right;

	type_right = (int *)((t_pipe *)root)->right;
	if (type_right)
	{
		if (*type_right == PIPE)
			return (true);
	}
	return (false);
}
