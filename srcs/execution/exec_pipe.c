/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:00:31 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:01 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <minishell.h>

static int	create_pipe(t_fork *frk);

static void	pipe_cleanup(t_fork *frk, int index)
{
	int	i;

	i = 0;
	while (i < index)
		free(frk->pipe[i++]);
	free (frk->pipe);
}

int	count_pipes(void *root)
{
	int		nbr_pipe;
	t_pipe	*pipe;

	nbr_pipe = 0;
	pipe = (t_pipe *)root;
	while (pipe && pipe->right)
	{
		++nbr_pipe;
		pipe = (t_pipe *)pipe->right;
	}
	return (nbr_pipe);
}

static t_fork	*init_tfork(int nbr_pipe)
{
	t_fork *frk;

	frk = (t_fork *)malloc(sizeof(t_fork));
	if (!frk)
		return (NULL);
	frk->fd_in = 0;
	frk->fd_out = 0;
	frk->nbr_cmds = nbr_pipe + 1;
	frk->pipe = (int **)malloc(sizeof(int *) * (frk->nbr_cmds - 1));
	if (!frk->pipe)
		return (NULL);
	frk->pid = malloc(sizeof(pid_t) * frk->nbr_cmds);
	if (!frk->pid)
		return (NULL);
	return (frk);
}

static int	create_pipe(t_fork *frk)
{
	int	i;

	i = 0;
	while (i < frk->nbr_cmds - 1)
	{
		frk->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!frk->pipe[i])
			return (pipe_cleanup(frk, i), 1);
		if (pipe(frk->pipe[i]) < 0)
			return (pipe_cleanup(frk, i), 1);
		i ++;
	}
	return (0);
}

t_fork	*handle_pipe(t_shell *shell, void *root)
{
	int		nbr_pipe;
	t_fork	*frk;

	if (check_pipe_rgt(root))
		nbr_pipe = count_pipes(root);
	else
		nbr_pipe = 1;
	frk = init_tfork(nbr_pipe);
	if (!frk)
		malloc_failure(shell, "handle_pipe");
	if (create_pipe(frk))
		malloc_failure(shell, "handle_pipe");
	return (frk);
}
