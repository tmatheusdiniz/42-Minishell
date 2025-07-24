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

static void	consume_input(t_heredoc *heredoc, int fd);

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
	if (current && (*(int *)current == EXEC || *(int *)current == BT))
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
			return (close(save_fdhere), -1); //handler
		consume_input(redir, fd[1]);
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		current = redir->next;
	}
	if (current && (*(int *)current == EXEC || *(int *)current == BT))
	{
		shell->root = current;
		aux_execution(shell, current);
	}
	dup2(save_fdhere, STDIN_FILENO);
	return (close (save_fdhere), 0);
}

static void	consume_input(t_heredoc *heredoc, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if ((line[ft_strlen(heredoc->delimiter)] == '\n'
				|| line[ft_strlen(heredoc->delimiter)] == '\0')
			&& !(ft_strncmp(line, heredoc->delimiter,
					ft_strlen(heredoc->delimiter))))
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
