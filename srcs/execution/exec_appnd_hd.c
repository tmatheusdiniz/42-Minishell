/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_appnd_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:17:37 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 16:42:27 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

static int	check_heredoc_errors(int save_fd);

static void	check_append_errors(char *file, int fd)
{
	close(fd);
	check_outredir_errors(file, fd);
}

int	exec_append(t_shell *shell, void *root)
{
	int			fd;
	int			save_fdout;
	void		*current;
	t_append	*redir;

	current = root;
	save_fdout = dup(STDOUT_FILENO);
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
		aux_execution(shell, current);
	}
	dup2(save_fdout, STDOUT_FILENO);
	return (close (save_fdout), 0);
}

int	exec_heredoc(t_shell *shell, void *root)
{
	int			fd[2];
	int			save_fdhere;
	void		*current;
	t_heredoc	*redir;

	current = root;
	save_fdhere = dup(STDIN_FILENO);
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
	{
		shell->root = current;
		aux_execution(shell, current);
	}
	return (dup2(save_fdhere, STDIN_FILENO), close(save_fdhere), 0);
}

static int	check_heredoc_errors(int save_fd)
{
	if (save_fd != -1)
		close(save_fd);
	if (errno == EMFILE || errno == ENFILE)
		ft_putstr_fd("minishell: heredoc: too many open files\n", 2);
	else if (errno == ENOMEM)
		ft_putstr_fd("minishell: heredoc: out of memory\n", 2);
	else if (errno == ENOSPC)
		ft_putstr_fd("minishell: heredoc: no space left on device\n", 2);
	else if (errno == EIO)
		ft_putstr_fd("minishell: heredoc: input/output error\n", 2);
	else if (errno == EFAULT)
		ft_putstr_fd("minishell: heredoc: bad address\n", 2);
	else if (errno == EINTR)
		ft_putstr_fd("minishell: heredoc: interrupted system call\n", 2);
	else if (errno == EPIPE)
		ft_putstr_fd("minishell: heredoc: broken pipe\n", 2);
	else
	{
		ft_putstr_fd("minishell: heredoc: error (", 2);
		ft_putnbr_fd(errno, 2);
		ft_putstr_fd(")\n", 2);
	}
	return (-1);
}
