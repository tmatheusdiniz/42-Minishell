/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:15:29 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/24 19:15:35 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_fork(t_shell *shell, t_fork *frk, int pipe_index)
{
	frk->pid[pipe_index] = fork();
	if (frk->pid[pipe_index] == 0)
		set_pipe(frk, pipe_index);
	else if (frk->pid[pipe_index] > 0)
		return ;
	else
		handle_errors(shell, "fork failed!", errno);
}
