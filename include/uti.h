/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:56:50 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/21 17:49:09 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include "./structs.h"

// ----------General----------
int		check_command(t_shell *shell, char **input);
int		ft_strcmp(char *s1, char *s2);
char	*check_space(char *input);
char	**duplicate_env_v(char **envp);
int		match_type(char *token);
bool	check_exec(char *token);
bool	check_builtin(char *token);
char	*check_env_var(char *input, int *i);

// ----------Linked List----------
int		get_index_env(t_env_v *env_v, char *var);
int		find_position(t_env_v *env_v, char *new_key, int linked_size);
int		count_linked_list(t_env_v *list);
void	*envp_to_linked_l(char **envp);
t_env_v	*get_node_envp(t_env_v *env_v, char *KEY);

// ----------Parsing----------
int		get_index_env_parsing(t_shell *mini, char *var);
char	*check_space(char *input);
int		match_type(char *token);
char	*clean_other_chars(char *var);
char	*clean_quotes(char *var, int i, int j);

//tree_utils.c
void	*create_exec_node(t_token *exec_token, int i);
void	*create_redir_node(t_token *redir_token, t_token *right_tokens);
void	*create_pipe_node(t_token *left_tokens, t_token *right_tokens);

//split_token.c
char	**split_token(char *str);

// ---------- *\ ----------

// free
void	free_structs(t_shell *shell);
void	clean_matrix(char **matrix);
void	clean_env_v(t_env_v *env);

#endif
