/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/21 14:44:03 by cda-fons         ###   ########.fr       */
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


//errors_utils.c
void	error_message(char *message, int errnbr);

//utils.c
int		get_index_env_parsing(t_shell *mini, char *var);
char	*check_space(char *input);
int		match_type(char *token);

//utils2.c
char	*clean_other_chars(char *var);
char	*clean_quotes(char *var);

//tokenizer.c
void	create_token_list(char **input_split, t_shell *mini, int i);

//parsing.c
//void	cmds(char **input_split, t_mini *mini);
char	**parsing(char *input, t_shell *mini);
bool	check_quotes(char *input_split, char quotes);

//expand.c
char	*expand(char *input, t_shell *mini);

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

#endif
