/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:32 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/03 16:50:22 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include <structs.h>

// ----------errors----------

void	handle_errors(t_shell *shell, char *message,
			int errnbr, char **inp_split);
void	error_message(char *message, int errnbr);

// ----------exit_code----------

int		exit_code(int value);
void	malloc_failure(t_shell *shell, char *function);


#endif
