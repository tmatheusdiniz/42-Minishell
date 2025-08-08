/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hered_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:17:37 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/08 16:22:09 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

static void	aux_exec_heredoc(t_shell *shell, void *current,
				t_fork *frk, int pipe_index);

static void	check_append_errors(char *file, int fd)
{
	close(fd);
	check_outredir_errors(file, fd);
}

int	exec_append(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	int			fd;
	int			save_fdout;
	void		*current;
	t_append	*redir;

	current = root;
	save_fdout = dup(STDOUT_FILENO);
	g_in_heredoc_or_pipe(1);
	while (current && *(int *)current == APPEND)
	{
		redir = (t_append *)current;
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd == -1)
			return (check_append_errors(redir->file, save_fdout), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		current = redir->next;
	}
	if (current)
	{
		shell->root = current;
		aux_exec_redir(shell, current, frk, pipe_index);
	}
	return (dup2(save_fdout, STDOUT_FILENO), close (save_fdout), 0);
}

static void	aux_exec_heredoc(t_shell *shell, void *current,
		t_fork *frk, int pipe_index)
{
	shell->root = current;
	aux_exec_redir(shell, current, frk, pipe_index);
}

int	exec_heredoc(t_shell *shell, void *root, t_fork *frk, int pipe_index)
{
	int			fd[2];
	int			save_fdhere;
	void		*current;
	t_heredoc	*redir;

	current = root;
	save_fdhere = dup(STDIN_FILENO);
	g_in_heredoc_or_pipe(1);
	while (current && *(int *)current == HEREDOC)
	{
		redir = (t_heredoc *)current;
		if (pipe(fd) == -1)
			return (check_heredoc_errors(save_fdhere), close(save_fdhere), -1);
		if (redir->content)
			write(fd[1], redir->content, ft_strlen(redir->content));
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		current = redir->next;
	}
	if (current)
		aux_exec_heredoc(shell, current, frk, pipe_index);
	return (dup2(save_fdhere, STDIN_FILENO), close(save_fdhere), 0);
}
