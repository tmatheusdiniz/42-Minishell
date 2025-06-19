/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:23:13 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/16 00:36:24 by mreinald         ###   ########.fr       */
/*   Updated: 2025/06/19 12:11:29 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_execution(t_shell *shell, t_exec *exec_node)
{
	(void)exec_node;
	if (check_whatis(shell->root) == EXEC)
		exit(0);
}
