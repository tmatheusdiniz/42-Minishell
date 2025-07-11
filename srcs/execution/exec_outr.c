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

void	exec_outredir(t_shell *shell, void *root)
{
	int			fd;
	void		*current;
	t_outredir	*outr;

	current = root;
	outr = (t_outredir *)current;
	while (current)
	{
		if (*(int *)root == OUTREDIR)
		{
			fd = open(outr->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (!fd)
				malloc_failure(shell, "EXEC_OUTREDIR_FD");
			dup2(fd, STDOUT_FILENO);
			close (fd);
			current = outr->next;
		}

	}
}
