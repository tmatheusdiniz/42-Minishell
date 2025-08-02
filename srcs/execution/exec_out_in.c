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

#include <minishell.h>

static void	check_errors(char *file, int fd);
static void	check_other_e(char *file);
static void	check_last_e(char *file);

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
		if (pipe_index != -4)
			aux_execution(shell, current, frk, pipe_index);
		else
			aux_no_pipe(shell, frk, current);
	}	
	dup2(save_fdout, STDOUT_FILENO);
	return (close (save_fdout), 0);
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
			return (check_errors(redir->file, save_fdin), -1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		current = redir->next;
	}
	if (current)
	{
		shell->root = current;
		if (pipe_index != -4)
			aux_execution(shell, current, frk, pipe_index);
		else
			aux_no_pipe(shell, frk, current);
	}
	dup2(save_fdin, STDIN_FILENO);
	return (close (save_fdin), 0);
}

static void	check_errors(char *file, int fd)
{
	close (fd);
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else
		check_other_e(file);
}

static void	check_other_e(char *file)
{
	if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else if (errno == ENAMETOOLONG)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": File name too long", 2);
	}
	else if (errno == ELOOP)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Too many symbolic links", 2);
	}
	else
		check_last_e(file);
}

static void	check_last_e(char *file)
{
	if (errno == EMFILE || errno == ENFILE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Too many open files", 2);
	}
	else if (errno == EIO)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Input/output error", 2);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Unknown error (", 2);
	ft_putnbr_fd(errno, 2);
	ft_putendl_fd(")", 2);
}
