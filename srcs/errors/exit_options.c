/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:08:41 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/03 16:42:37 by cda-fons         ###   ########.fr       */
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

void	error_message(char *message, int errnbr)
{
	errnbr = 2;
	ft_putendl_fd(message, errnbr);
}

void	handle_errors(t_shell *shell, char *message,
		int errnbr, char **inp_split)
{
	if (inp_split)
		free (inp_split);
	free_structs(shell);
	error_message(message, errnbr);
	exit(errnbr);
}