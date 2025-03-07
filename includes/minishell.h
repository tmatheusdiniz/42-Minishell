/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/06 15:25:00 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> 
# include <stdio.h> 
# include <unistd.h> 
# include <sys/wait.h> 
# include <sys/types.h> 
# include <fcntl.h> 
# include <termio.h> 
# include <signal.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../Libft/libft.h"
# include <sys/stat.h>

# define NAME_SHELL "Minishell: "


typedef	struct	s_mini
{
	char	**args;
	char	**env;
}				t_mini;


//safe_utils.c
void safe_cd(char *chdir_arg, int flag);

//errors_utils.c
void	error_message(int errnbr, char *message);
void	mini_errors(t_mini *mini, char *message, int errnbr);

//exits.c
void	exit_mini(t_mini *mini, int errnbr);

//			builtins
//cd
void	cd(t_mini *mini);
char *get_target(char **args);
int	change_dir(char *target);
void update_env(char *cwd);

//env
int	env(char **args);

//pwd
int	pwd(void);

#endif