/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:55:32 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/13 18:49:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include <structs.h>

// ----------Errors----------
void	handle_errors(t_shell *shell, char *message,
			int errnbr);
void	error_message(char *message, int errnbr);

// ----------Redir----------
void	check_outredir_errors(char *file, int fd);
int		check_heredoc_errors(int save_fd);

// ----------exit_code----------
int		exit_code(int value);
void	malloc_failure(t_shell *shell, char *function);

// ----------Execution----------
void	check_errors_inredir(char *file, int fd);
void	print_export_error(char *identifier);
void	print_command_notf(char *str);

#endif
