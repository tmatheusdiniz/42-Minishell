/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:56:50 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/16 00:23:14 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <structs.h>
# include <stdbool.h>

// ----------Main----------
int		check_args(int argc, char const **argv, char **envp);
void	handle_env_vars(t_shell *shell, char **envp);
t_shell	*init_shell(void);
t_exec	*find_t_exec(void *root);

// ----------Linked List----------
int		get_index_env(t_env_v *env_v, char *var);
int		find_position(t_env_v *env_v, char *new_key, int linked_size);
int		linked_env_size(t_env_v *list);
t_env_v	*envp_to_linked_l(char **envp);
t_env_v	*get_node_envp(t_env_v *env_v, char *KEY);

// ----------Print----------
void	print_exit(void);
int		print_error(char *str1, char *str2, char *str3, char *message);

// ----------General----------
int		ft_strcmp(char *s1, char *s2);
char	*check_space(char *input);
char	**linked_to_envp(t_shell *shell);
int		match_type(char *token);
bool	check_if_exec(char *token);
bool	check_builtin(char *token);
char	*check_env_var(char *input, int *i);

// ----------Parsing----------
t_env_v	*get_env_node_parsing(t_shell *mini, char *var, t_env_v	*current);
char	*check_space(char *input);
int		match_type(char *token);
char	*clean_other_chars(char *var);
char	*clean_quotes(char *var, int i, int j);
bool	expand_check(char *input);

//tree_utils.c
void	*create_exec_node(t_token *exec_token, int i);
void	*create_redir_node(t_token *redir_token, t_token *right_tokens, 
		t_token *left_tokens);
void	*create_pipe_node(t_token *left_tokens, t_token *right_tokens);
void	*aux_redir_node(t_token *redir_token, t_token	*file_token, 
		t_token	*recombined_list);
void	*create_inredir(t_token *right_tokens, void *next_node);
void	*create_append(t_token *right_tokens, void *next_node);
void	*create_heredoc(t_token *right_tokens, void *next_node);
void	*create_outredir(t_token *right_tokens, void *next_node);

//split_token.c
char	**split_token(char *str);

#endif
