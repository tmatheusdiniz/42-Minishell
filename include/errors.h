/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:32 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/22 17:44:53 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include "./structs.h"

// errors
void	handle_errors(t_shell *shell, char *message,
			int errnbr, char **inp_split);
void	error_message(char *message, int errnbr);
int		print_error(char *str1, char *str2, char *str3, char *message);

#endif
