/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:32 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/08 13:56:17 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include "./structs.h"

// errors
void	handle_errors(t_shell *shell, char *message,
			int errnbr, char **inp_split);
void	error_message(char *message, int errnbr);

#endif
