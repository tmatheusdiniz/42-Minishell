/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/11 16:36:22 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libft
# include "../lib/include/libft.h"

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
# include "builtins.h"
# include "structs.h"
# include "errors.h"
# include "colors.h"
# include "signals.h"
# include "utils.h"

# define NAME_SHELL "Minishell: "

<<<<<<< HEAD:include/minishell.h
// core
int		main(int argc, char const **argv, char **envp);

#endif
=======
# define CMD 1
# define EXEC  2
# define PIPE  3
# define OUTREDIR 4
# define INREDIR 5
# define APPEND 6
# define HEREDOC 7
# define ARG 8
# define EXIT_EOF 10
# define EXIT_CMD 11

typedef struct s_token	t_token;
typedef struct s_exec	t_exec;
typedef struct s_redir	t_redir;
typedef struct s_pipe	t_pipe;

typedef struct s_exec
{
	int		type;
	char	**argv;
}				t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	void	*next;
}				t_redir;

typedef struct s_pipe
{
	int		type;
	void	*left;
	void	*right;
}				t_pipe;

typedef struct s_token
{
	char	*token;
	int		type;
	int		index;
	t_token	*next;
	t_token	*prev;
}				t_token;

typedef struct s_mini
{
	char	**env;
	void	*root;
	t_token	*tokens;
}				t_mini;

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
int		match_type(char *token);

//utils2.c
char	*clean_other_chars(char *var);
char	*clean_quotes(char *var);

//free.c
void	free_mini(t_mini *mini, char *message, int errnbr, char **input_split);
int		print_error(char *str1, char *str2, char *str3, char *message);
void	free_token(t_token **token);

//tokenizer.c
//char	**tokenizer(char *input);
void	create_token_list(char **input_split, t_mini *mini, int i);

//parsing.c
void	cmds(char **input_split, t_mini *mini);
char	**parsing(char *input, t_mini *mini);
bool	check_quotes(char *input_split, char quotes);

//expand.c
char	*expand(char *input, t_mini *mini);

//tree.c
t_token	*search_redir(t_token *token);
t_token	*search_pipe(t_token *token);
void	*build_tree(t_token *tokens);
void	cut_tokens(t_token *tokens, t_token *base, t_token **left_tokens,
			t_token **right_tokens);

//tree_utils.c
void	*create_exec_node(t_token *exec_token, int i);
void	*create_redir_node(t_token *redir_token, t_token *right_tokens);
void	*create_pipe_node(t_token *left_tokens, t_token *right_tokens);

//split_token.c
char	**split_token(char *str);

//signals.c
void	signal_init(void);
void	signal_handler(int sig);

#endif
>>>>>>> Parsing:includes/minishell.h
