/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:14:21 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/19 22:30:49 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->input_split = NULL;
	shell->cwd = NULL;
	shell->root = NULL;
	shell->tokens = NULL;
}

void	free_redir(void *root)
{
	t_redir	*redir;

	redir = (t_redir *)root;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_tree(redir->next);
}

void	free_exec(void *root)
{
	t_exec	*exec;

	exec = (t_exec *)root;
	if (exec->argv)
		clean_matrix(exec->argv);
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
	else if (type == OUTREDIR
		|| type == INREDIR
		|| type == APPEND)
		free_redir(root);
	free(root);
}

void	free_shell_part(t_shell *shell)
{
	if (shell->input)
		free (shell->input);
	if (shell->input_split)
		free (shell->input_split);
	if (shell->cwd)
		free (shell->cwd);
	if (shell->root)
		free_tree(shell->root);
	reset_shell(shell);
}
