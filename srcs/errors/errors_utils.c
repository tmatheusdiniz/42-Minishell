/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:23:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/18 16:46:49 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// temporary, after add other many more things for handle errors

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
