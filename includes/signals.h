/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:58:43 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/08 13:58:59 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <structs.h>
# include <signal.h>

// signals
void	signal_handler(void);
void	signal_ctrl(int signal);

// Heredoc
int		g_in_heredoc_or_pipe(int nbr);

#endif
