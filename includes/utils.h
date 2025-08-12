/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:56:50 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/09 23:57:28 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <structs.h>
# include <stdbool.h>

// ----------Main----------
int			check_args(int argc, char const **argv, char **envp);
void		handle_env_vars(t_shell *shell, char **envp);
t_shell		*init_shell(void);

// ----------Linked List----------
int			get_index_env(t_env_v *env_v, char *var);
int			find_position(t_env_v *env_v, char *new_key, int linked_size);
int			linked_env_size(t_env_v *list);
t_env_v		*envp_to_linked_l(char **envp);
t_env_v		*get_node_envp(t_env_v *env_v, char *KEY);

// ----------Print----------
void		print_exit(void);
int			print_error(char *str1, char *str2, char *str3, char *message);

// ----------General----------
int			ft_strcmp(char *s1, char *s2);
char		*check_space(char *input);
char		**linked_to_envp(t_shell *shell);
int			match_type(char *token);
bool		check_if_exec(char *token);
bool		check_builtin(char *token);
char		*check_env_var(char *input, int *i);

// ----------Parsing----------
t_env_v		*get_env_node_parsing(t_shell *mini, char *var, t_env_v	*current);
char		*check_space(char *input);
int			match_type(char *token);
char		*clean_other_chars(char *var);
char		*clean_quotes(char *var, int i, int j);
bool		expand_check(char *input);
char		*aux_handle_exit_expand(char *string, int *inc);
char		*handle_exit_status(int *inc);
char		*aux_handle_literal_dollar(int *inc, char *input, char *env_var);
char		**prepare_argv_for_exec(char **argv);
bool		check_closed_quotes(char *input_split, char quotes);
bool		check_heredoc_signal_on_input(char *input);
bool		only_pipe_validations(char *input);
bool		check_especial_caracters(char *input);
void		aux_heredoc_content(char *line, char *delimiter, int free_delim);
bool		check_delimiter_heredoc(char **input_split, int i);

//tree_utils.c
void		*create_exec_node(t_token *exec_token, int i);
void		*create_redir_node(t_token *redir_token, t_token *right_tokens,
				t_token *left_tokens);
void		*create_pipe_node(t_token *left_tokens, t_token *right_tokens);
void		*aux_redir_node(t_token *redir_token, t_token	*file_token,
				t_token	*recombined_list);
void		*create_inredir(t_token *right_tokens, void *next_node);
void		*create_append(t_token *right_tokens, void *next_node);
void		*create_heredoc(t_token *right_tokens, void *next_node);
void		*create_outredir(t_token *right_tokens, void *next_node);

//utils_token.c
void		free_all_collected_tokens(t_tokens *data);
t_tokens	*collect_all_tokens(t_token *tokens);

//split_token.c
char		**split_token(char *str);

#endif
