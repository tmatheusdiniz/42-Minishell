/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:08:41 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/24 21:00:58 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_failure(t_shell *shell, char *function)
{
	if (shell)
		free_shell(shell);
	ft_putstr_fd(RED"MALLOC ERROR"DEFAULT, 2);
	ft_putendl_fd(function, 2);
	exit (1);
}
