/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:40:33 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/18 09:45:49 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_outr_other(char *file);
static void	check_outr_last(char *file);
static void	aux_check_outr(char *file);

int	check_heredoc_errors(int save_fd)
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

void	check_outredir_errors(char *file, int fd)
{
	close(fd);
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
		check_outr_other(file);
}

static void	check_outr_other(char *file)
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
		aux_check_outr(file);
}

static void	aux_check_outr(char *file)
{
	if (errno == EMFILE || errno == ENFILE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Too many open files", 2);
	}
	else
		check_outr_last(file);
}

static void	check_outr_last(char *file)
{
	if (errno == EIO)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Input/output error", 2);
	}
	else if (errno == ENOSPC)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No space left on device", 2);
	}
	else if (errno == EROFS)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Read-only file system", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Unknown error (", 2);
		ft_putendl_fd(")", 2);
	}
}
