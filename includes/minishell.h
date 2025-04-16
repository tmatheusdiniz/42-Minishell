/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/16 20:53:27 by cda-fons         ###   ########.fr       */
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
# include "../Lib/Libft/libft.h"
# include <sys/stat.h>

# define NAME_SHELL "Minishell: "

typedef struct s_mini
{
	char	**env;
}				t_mini;

typedef struct s_token
{
	char	*token;
	char	*type;
}				t_token;

//errors_utils.c
void	error_message(char *message, int errnbr);
void	mini_errors(t_mini *mini, char *message, int errnbr);

//			builtins
//cd.c
int		cd(t_mini *mini, char **input);
char	*get_target(char *input, t_mini *mini);
int		change_dir(t_mini *mini, char *target);
void	update_oldpwd(t_mini *mini);
void	update_pwd(t_mini *mini);

//env.c
char	**duplicate_env(char **envp);
int		env(char **args);

//pwd.c
int		pwd(void);

//echo.c
int		echo(char **input);

//unset.c
int		size_env(t_mini *mini);
char	**new_env(t_mini *mini, int index_to_unset);
int		unset(t_mini *mini, char *var);

//utils.c
int		get_index_env(t_mini *mini, char *var);
char	*check_space(char *input);

//free.c
void	free_mini(t_mini *mini, char *message, int errnbr, char **input_split);

//tokenizer.c
char	**tokenizer(char *input);

//parsing.c
void	cmds(char **input_split, t_mini *mini);
char	**parsing(char *input, t_mini *mini);

//split_token.c
char	**split_token(char *str);

//signals.c
void	signal_init(void);
void	signal_handler(int sig);

#endif