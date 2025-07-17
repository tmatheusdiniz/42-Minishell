/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:17:37 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/16 14:32:29 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
				return (close(save_fdout), perror("open"), 1);
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
