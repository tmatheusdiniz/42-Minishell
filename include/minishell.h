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

# include "../lib/Libft/include/libft.h"
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
# include <sys/stat.h>

# define NAME_SHELL "Minishell: "

typedef struct s_env_v
{
	char		*KEY;
	char		*VALUE;
	struct s_env_v	*next;
}		t_env_v;

typedef struct s_mini
{
	char	**env;
	t_env_v	*env_v;
}		t_mini;


// core
int		main(int argc, char const **argv, char **envp);

// ----------builtins----------

//errors_utils.c
void	error_message(char *message, int errnbr);
void	mini_errors(t_mini *mini, char *message, int errnbr);

//			builtins

//cd
int		cd(t_mini *mini, char **input);
char	*get_target(char *input, t_mini *mini);
int		change_dir(t_mini *mini, char *target);
void	update_oldpwd(t_mini *mini);
void	update_pwd(t_mini *mini);

// env
char	**duplicate_env(char **envp);
int		env(char **args);

// pwd
int		pwd(void);

// echo
int		echo(char **input);

// unset
int		size_env(t_mini *mini);
char	**new_env(t_mini *mini, int index_to_unset);
int		unset(t_mini *mini, char *var);

// export
void	export_func(t_mini *mini, char *argument);


// ----------*/----------

// utils.c

// ----------export----------
void	*envp_to_l_l(char **envp);
void	*create_node(char *key_name, char *content);
void	set_only_key(char *key, t_env_v *env_v);

// ----------General----------
int		get_index_env(t_mini *mini, char *var);
char	*check_space(char *input);
int		check_ifis_bt(t_mini *mini, char **input);
int		ft_strcmp(char *s1, char *s2);


// errors
void	error_message(char *message, int errnbr);
void	mini_errors(t_mini *mini, char *message, int errnbr);

//free.c
void	free_mini(t_mini *mini, char *message, int errnbr, char **input_split);

//signals
void	signal_init(void);
void	signal_handler(int sig);

#endif
