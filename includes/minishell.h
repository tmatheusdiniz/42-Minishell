/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 13:20:17 by cda-fons         ###   ########.fr       */
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
# include <structs.h>
# include <errors.h>
# include <colors.h>
# include <signals.h>
# include <control.h>
# include <utils.h>
# include <input.h>

/*
# define ESC_START	"\001\033[1;31m\002"
# define ESC_CODE	"\001\033[1;34m\002"
# define ESC_PROMPT	"\001\033[1;32m\002"
# define SHELL_NAME "[Minishell]"
# define SYMBOL		"➜ "
*/

# define ESC_START "\001\033[1;91m\002"
# define ESC_GREEN "\001\033[0;92m\002"
# define ESC_RESET "\001\033[0m\002"
# define PROMPT_START "\001\033[1;91m\002Minishell[\001\033[0;92m\002"
# define PROMPT_MID "\001\033[1;91m\002][\001\033[0;92m\002"
# define PROMPT_END "\001\033[1;91m\002] \001\033[0m\002→ "

// core
int		main(int argc, char const **argv, char **envp);

#endif
