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
# include "../lib/Libft/include/libft.h"

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
#include <limits.h>
#include <dirent.h>

// Terminal Control
#include <termio.h>

# define NAME_SHELL "Minishell: "

// core
int		main(int argc, char const **argv, char **envp);

#endif
