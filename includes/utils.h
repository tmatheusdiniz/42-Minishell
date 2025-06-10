/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:56:50 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/09 20:38:23 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <structs.h>
# include <stdbool.h>

// ----------Main----------
int		check_args(int argc, char const **argv, char **envp);
int		check_command(t_shell *shell, t_exec *exec_node);
void	handle_env_vars(t_shell *shell, char **envp);
t_shell	*init_shell(void);

// ----------Linked List----------
int		get_index_env(t_env_v *env_v, char *var);
int		find_position(t_env_v *env_v, char *new_key, int linked_size);
int		linked_env_size(t_env_v *list);
t_env_v	*envp_to_linked_l(char **envp);
t_env_v	*get_node_envp(t_env_v *env_v, char *KEY);

// ----------Print----------
void	print_exit(void);
int		print_error(char *str1, char *str2, char *str3, char *message);

// free
void	free_shell(t_shell *shell);
void	free_env_v(t_env_v *env_v);
void	clean_matrix(char **matrix);
void	free_env_v(t_env_v *env_v);

// ----------General----------
int		ft_strcmp(char *s1, char *s2);
char	*check_space(char *input);
char	**linked_to_envp(t_shell *shell);
int		match_type(char *token);
bool	check_exec(char *token);
bool	check_builtin(char *token);
char	*check_env_var(char *input, int *i);

// ----------Control----------
void	free_shell_part(t_shell *shell);

// ----------Parsing----------
t_env_v	*get_env_node_parsing(t_shell *mini, char *var, t_env_v	*current);
char	*check_space(char *input);
int		match_type(char *token);
char	*clean_other_chars(char *var);
char	*clean_quotes(char *var, int i, int j);
bool	expand_check(char *input);

//tree_utils.c
void	*create_exec_node(t_token *exec_token, int i);
void	*create_redir_node(t_token *redir_token, t_token *right_tokens);
void	*create_pipe_node(t_token *left_tokens, t_token *right_tokens);

//split_token.c
char	**split_token(char *str);

// ---------- *\ ----------

// free
void	clean_matrix(char **matrix);

#endif
