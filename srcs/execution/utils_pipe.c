/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:01:38 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/30 15:01:45 by mreinald         ###   ########.fr       */
/*   Created: 2025/06/28 20:01:08 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/28 20:01:17 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	tree_has_redirections(void *root)
{
	t_pipe		*pipe_node;

	if (!root)
		return (false);
	if (*(int *)root == PIPE)
	{
		pipe_node = (t_pipe *)root;
		return (tree_has_redirections(pipe_node->left)
			|| tree_has_redirections(pipe_node->right));
	}
	else if (*(int *)root == OUTREDIR)
		return (true);
	else if (*(int *)root == INREDIR)
		return (true);
	else if (*(int *)root == APPEND)
		return (true);
	else if (*(int *)root == HEREDOC)
		return (true);
	return (false);
}

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
		if (!tree_has_redirections(frk->root))
		{
			dup2(frk->pipe[pipe_index - 1][0], STDIN_FILENO);
			close(frk->pipe[pipe_index - 1][0]);
		}
		close(frk->pipe[pipe_index - 1][1]);
	}
	if (pipe_index < frk->nbr_cmds - 1)
	{
		if (!tree_has_redirections(frk->root))
		{
			dup2(frk->pipe[pipe_index][1], STDOUT_FILENO);
			close(frk->pipe[pipe_index][1]);
		}
		close(frk->pipe[pipe_index][0]);
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
