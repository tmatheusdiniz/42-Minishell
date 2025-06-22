/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:00:31 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:01 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <minishell.h>

int	count_pipes(void *root)
{
	int		nbr_pipe;
	t_pipe	*pipe;

	nbr_pipe = 0;
	pipe = (t_pipe *)root;
	while (pipe && pipe->right)
	{
		++nbr_pipe;
		pipe = (t_pipe *)pipe->right;
	}
	return (nbr_pipe);
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

int	check_pipe_lft(void *root)
{
	int	*type_left;

	type_left = (int *)((t_pipe *)root)->left;
	if (*type_left == BT)
		return (BT);
	if (*type_left == EXEC)
		return (EXEC);
	else if (*type_left == INREDIR)
		return (INREDIR);
	else if (*type_left == OUTREDIR)
		return (OUTREDIR);
	else if (*type_left == HEREDOC)
		return (HEREDOC);
	else if (*type_left == APPEND)
		return (APPEND);
	return (0);
}
