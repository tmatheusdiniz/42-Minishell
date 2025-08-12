/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:08:41 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/13 18:48:54 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_failure(t_shell *shell, char *function)
{
	if (shell)
		free_shell_final(shell);
	ft_putstr_fd(RED"MALLOC ERROR->"DEFAULT, 2);
	ft_putendl_fd(function, 2);
	exit (1);
}

void	error_message(char *message, int errnbr)
{
	ft_putendl_fd(message, errnbr);
}

void	handle_errors(t_shell *shell, char *message,
		int errnbr)
{
	free_shell_final(shell);
	error_message(message, errnbr);
	exit(errnbr);
}

int	exit_code(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}
