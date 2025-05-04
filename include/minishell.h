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
	char			*key;
	char			*value;
	struct s_env_v	*next;
}		t_env_v;

typedef struct s_mini
{
	t_env_v	*env_v;
	char	*input;
	char	**envp;
}		t_mini;

// core
int		main(int argc, char const **argv, char **envp);

// ----------builtins----------

// built-ins

// cd
int		cd(t_mini *mini, char **input);
char	*get_target(t_env_v *env_v, char *input);
int		change_dir(t_env_v *env_v, char *target);
void	update_pwd(t_env_v *env_v);
void	update_oldpwd(t_env_v *env_v);

// env
int		env(t_env_v *env_v);

// pwd
int		pwd(void);

// echo
int		echo(char **input);

// unset
int		unset(t_mini *mini, char *env_var);

// export
void	export_func(t_mini *mini, char *argument);

// ----------*/----------

// utils

// ----------export----------
char	**aux_set(char *envp);
void	*create_node(char *key_name, char *content);
t_env_v	*set_only_key(t_env_v *env_v, char *key);
void	ft_sort_linked(t_env_v *env_v);

// ----------General----------
char	**duplicate_env_v(char **envp);
char	*check_space(char *input);
int		check_command(t_mini *mini, char **input);
int		ft_strcmp(char *s1, char *s2);

// ----------Linked List----------
void	*envp_to_linked_l(char **envp);
t_env_v	*get_node_envp(t_env_v *env_v, char *KEY);
int		get_index_env(t_env_v *env_v, char *var);
int		count_linked_list(t_env_v *list);

// errors
void	handle_errors(t_mini *mini, char *message,
			int errnbr, char **inp_split);
void	error_message(char *message, int errnbr);

// free
void	free_structs(t_mini *mini);
void	clean_matrix(char **matrix);

// signals
void	signal_init(void);
void	signal_handler(int sig);

#endif
