/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:14:21 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 23:47:35 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->cwd = NULL;
	shell->root = NULL;
	shell->original_root = NULL;
	shell->tokens = NULL;
}

void	free_exec(void *root)
{
	t_exec	*exec;

	exec = (t_exec *)root;
	if (exec->argv)
		clean_matrix(exec->argv);
	if (exec->cmd_path)
		free (exec->cmd_path);
}

void	free_tree(void *root)
{
	int		type;
	t_pipe	*pipe;

	if (!root)
		return ;
	type = *(int *)root;
	if (type == PIPE)
	{
		pipe = (t_pipe *)root;
		free_tree(pipe->left);
		free_tree(pipe->right);
	}
	else if (type == EXEC || type == BT)
		free_exec(root);
	else if (type == OUTREDIR)
		free_outredir(root);
	else if (type == INREDIR)
		free_inredir(root);
	else if (type == APPEND)
		free_append(root);
	else if (type == HEREDOC)
		free_heredoc(root);
	free(root);
	root = NULL;
}

void	free_shell_part(t_shell *shell)
{
	if (shell->input)
		free (shell->input);
	if (shell->cwd)
		free (shell->cwd);
	if (shell->original_root)
		free_tree(shell->original_root);
	reset_shell(shell);
}
