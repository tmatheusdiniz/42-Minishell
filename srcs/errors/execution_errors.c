/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:15:55 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/02 13:17:07 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_other_e(char *file);
static void	check_last_e(char *file);

void	print_export_error(char *identifier)
{
	if (identifier && (identifier[0] == '-' || identifier[0] == '+'))
	{
		if (identifier[1] == '=')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(identifier, 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("export: usage: export ", 2);
			ft_putendl_fd("[-fn] [name[=value] ...] or export -p ", 2);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(identifier, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(identifier, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
}

void	print_command_notf(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

void	check_errors_inredir(char *file, int fd)
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
