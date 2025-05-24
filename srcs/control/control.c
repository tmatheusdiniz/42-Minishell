/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:06 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/21 14:45:06 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <minishell.h>

void	control(t_shell *shell, char **envp)
{
	(void)envp;
	shell->input = readline("Minishell: ");
	if (!shell->input)
		return ; // Temporary handle
	signal_handler();
	control(shell, envp);
}

