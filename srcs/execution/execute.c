/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:49:38 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/21 21:54:55 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_execution(t_shell *shell, t_exec *exec_node)
{
	int	nbr_pipe;
	(void)exec_node;
	if (*(int *)shell->root == PIPE)
	{
		if (check_pipe_rgt(shell->root))
			nbr_pipe = count_pipes(shell->root);
		else
			nbr_pipe = 1;
		if (check_pipe_lft(shell->root) == BT)
				; // to call something
		else if (check_pipe_lft(shell->root) == EXEC)
				; // ...
		else if (check_pipe_lft(shell->root) == INREDIR)
				; // ...
		else if (check_pipe_lft(shell->root) == OUTREDIR)
				;
		else if (check_pipe_lft(shell->root) == HEREDOC)
				;
		else if (check_pipe_lft(shell->root) == APPEND)
				;
	}
}
