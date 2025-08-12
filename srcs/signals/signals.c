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

#include "signals.h"
#include <minishell.h>

volatile sig_atomic_t	g_sigint_received = 0;

static void	aux_signal(void)
{
	write(2, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_code(130);
	g_sigint_received = 1;
}

static void	heredoc_signal(void)
{
	write(2, "^C", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit_code(130);
	g_define_sign(130);
	g_sigint_received = 1;
}

void	signal_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		if (g_executing(-1) == 1)
		{
			write(2, "\n", 1);
			return ;
		}
		else if (g_define_sign(-1) == 1)
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_point = 0;
			rl_end = 0;
			rl_done = 1;
			rl_on_new_line();
			exit_code(130);
			g_define_sign(0);
			return ;
		}
		else if (g_define_sign(-1) == 2)
			heredoc_signal();
		else
			aux_signal();
	}
}

int	check_sigint_event(void)
{
	if (g_sigint_received)
	{
		g_sigint_received = 0;
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	signal_handler(void)
{
	signal(SIGINT, signal_ctrl);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	rl_catch_signals = 0;
	rl_event_hook = check_sigint_event;
}

/*
static void	heredoc_signal(void);

static void	aux_signal(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_code(130);
}

static void	heredoc_signal(void)
{
	rl_replace_line("", 0);         // Clear current input
    rl_on_new_line();
    exit_code(130);
    g_in_heredoc_or_pipe(130);
}

void	signal_ctrl(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		if (g_executing_command)
			return ;
		else if (g_in_heredoc_or_pipe(-1) == 1)
		{
			rl_replace_line("", 0);
			rl_point = 0;
			rl_end = 0;
			rl_done = 1;
			rl_on_new_line();
			exit_code(130);
			g_in_heredoc_or_pipe(0);
			return ;
		}
		else if (g_in_heredoc_or_pipe(-1) == 2)
			heredoc_signal();
		else
			aux_signal();
	}
}

void	signal_handler(void)
{
	signal(SIGINT, signal_ctrl);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
*/
