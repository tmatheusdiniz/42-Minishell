/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:19:00 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/08 16:21:42 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t g_executing_command = 0;

void	signal_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		if (g_executing_command)
		{
			write(2, "\n", 1);
			return ;
		}
		if (g_in_heredoc_or_pipe(-1) == 1)
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_point = 0;
			rl_end = 0;
			rl_done = 1;
			rl_on_new_line();
			exit_code(130);
			g_in_heredoc_or_pipe(0);
			return ;
		}
		else
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			exit_code(130);
		}
	}
}

void	signal_handler(void)
{
	signal(SIGINT, signal_ctrl);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
