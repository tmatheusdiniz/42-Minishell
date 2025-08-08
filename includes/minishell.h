/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/08/08 16:21:08 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libft
# include <libft.h>

// Standard Libraries
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// POSIX and System Headers
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

// Limits and Directory
# include <limits.h>
# include <dirent.h>

// Terminal Control
# include <termio.h>

// System
# include <builtins.h>
# include <execution.h>
# include <parsing.h>
# include <structs.h>
# include <errors.h>
# include <colors.h>
# include <signals.h>
# include <input.h>
# include <utils.h>
# include <free.h>

# define NAME_SHELL "minishell"
# define ESC_START "\001\033[1;91m\002"
# define ESC_GREEN "\001\033[0;92m\002"
# define ESC_RESET "\001\033[0m\002"
# define PROMPT_START "\001\033[1;91m\002Minishell[\001\033[0;92m\002"
# define PROMPT_MID "\001\033[1;91m\002][\001\033[0;92m\002"
# define PROMPT_END "\001\033[1;91m\002] \001\033[0m\002→ "

# define BT 1
# define EXEC 2
# define PIPE 3
# define OUTREDIR 4
# define INREDIR 5
# define APPEND 6
# define HEREDOC 7
# define ARG 8
# define EXIT_EOF 10
# define EXIT_CMD 11

// Global Var
extern volatile sig_atomic_t	g_executing_command;

// core

int		main(int argc, char const **argv, char **envp);

// Control
void	control(t_shell *shell, char **envp);

#endif
