/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_out_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:27:51 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/29 18:53:39 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>

static void	aux_exec_inredir(t_shell *shell, void *current,
				t_fork *frk, int pipe_index);

static void	aux_exec_outredir(t_shell *shell, void *current,
		t_fork *frk, int pipe_index)
{
	if (pipe_index != -4)
		aux_execution(shell, current, frk, pipe_index);
	else
		aux_no_pipe(shell, frk, current);
}

int	exec_outredir(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	int			fd;
	int			save_fdout;
	void		*current;
	t_outredir	*redir;

	current = root;
	save_fdout = dup(STDOUT_FILENO);
	while (current && *(int *)current == OUTREDIR)
	{
		redir = (t_outredir *)current;
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd == -1)
			return (check_outredir_errors(redir->file, save_fdout), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		current = redir->next;
	}
	if (current)
	{
		shell->root = current;
		aux_exec_outredir(shell, current, frk, pipe_index);
	}
	dup2(save_fdout, STDOUT_FILENO);
	return (close (save_fdout), 0);
}

static void	aux_exec_inredir(t_shell *shell, void *current,
		t_fork *frk, int pipe_index)
{
	if (pipe_index != -4)
		aux_execution(shell, current, frk, pipe_index);
	else
		aux_no_pipe(shell, frk, current);
}

int	exec_inredir(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	int			fd;
	int			save_fdin;
	void		*current;
	t_inredir	*redir;

	current = root;
	save_fdin = dup(STDIN_FILENO);
	while (current && *(int *)current == INREDIR)
	{
		redir = (t_inredir *)current;
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (check_errors_inredir(redir->file, save_fdin), -1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		current = redir->next;
	}
	if (current)
	{
		shell->root = current;
		aux_exec_inredir(shell, current, frk, pipe_index);
	}
	dup2(save_fdin, STDIN_FILENO);
	return (close (save_fdin), 0);
}
