/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:49:38 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/08 16:49:56 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_tree_recur(t_shell *shell, void *root,
		t_fork *frk, int pipe_index)
{
	t_pipe	*pipe_root;

	if (!root)
		return ;
	if (*(int *)root == PIPE)
	{
		pipe_root = (t_pipe *)root;
		execute_tree_recur(shell, pipe_root->left, frk, pipe_index);
		execute_tree_recur(shell, pipe_root->right, frk, pipe_index + 1);
	}
	else if (*(int *)root == BT || *(int *)root == EXEC)
		ft_execute_cmmd(shell, root, frk, pipe_index);
	else if (*(int *)root == OUTREDIR || *(int *)root == INREDIR
		|| *(int *)root == APPEND || *(int *)root == HEREDOC)
		aux_execution(shell, root, frk, pipe_index);
}
