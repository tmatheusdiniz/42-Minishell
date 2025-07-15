/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:27:51 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/09 14:34:41 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "structs.h"
#include <fcntl.h>
#include <minishell.h>
#include <unistd.h>

/*
void	exec_outredir(t_shell *shell, void *root)
{
	int			fd;
	void		*current;
	t_outredir	*outr;

	current = root;
	outr = (t_outredir *)root;
	while (current)
	{
		if (*(int *)current == OUTREDIR)
		{
			fd = open(outr->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (!fd)
				malloc_failure(shell, "EXEC_OUTREDIR_FD");
			dup2(fd, STDOUT_FILENO);
			close (fd);
			outr = outr->next;
			current = outr;
		}
		else if (*(int *)current == EXEC || *(int *)current == BT)
		{
			shell->root = current;
			aux_execution(shell, current);
			outr = outr->next;
			current = outr;
		}
	}
}
*/

void	exec_outredir(t_shell *shell, void *root)
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
		//printf("DEBUG: Abrindo arquivo: %s\n", redir->file);
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd == -1)
			return ;
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
	close (save_fdout);
}
