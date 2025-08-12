/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:23:56 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/08 16:57:26 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <structs.h>

// ----------Execute----------
void	ft_execution(t_shell *shell);
void	execute_tree_recur(t_shell *shell, void *root,
			t_fork *frk, int pipe_index);
void	ft_execute_cmmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index);

// ----------Execute Redir----------
int		exec_outredir(t_shell *shell, void *root, t_fork *frk, int pipe_index);
int		exec_inredir(t_shell *shell, void *root, t_fork *frk, int pipe_index);
int		exec_append(t_shell *shell, void *root, t_fork *frk, int pipe_index);
int		exec_heredoc(t_shell *shell, void *root, t_fork *frk, int pipe_index);
void	aux_exec_redir(t_shell *shell, void *current,
			t_fork *frk, int pipe_index);
void	read_all_heredocs(void *root);
void	read_all_heredocs_with_shell(void *root, t_shell *shell);
void	aux_read_hd(void *root, t_shell *shell);
int		has_quotes(char *delimiter);
char	*remove_delimiter_quotes(char *delimiter);

// ----------Utils Execute----------
void	aux_execution(t_shell *shell, void *root, t_fork *frk, int pipe_index);
void	execute_no_pipe(t_shell *shell, t_fork *frk);
void	aux_no_pipe(t_shell *shell, t_fork *frk, void *root);
char	*aux_set_with_append(t_shell *shell, t_env_v *current,
			char **splt, char *key);

// ----------Utils Pipe----------
t_fork	*handle_pipe(t_shell *shell, void *root);
bool	check_pipe_rgt(void	*root);
int		count_pipes(void *root);
void	set_pipe(t_fork *frk, int pipe_index);

// ----------Utils Execute----------
void	check_lastcmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index);
void	child_cleanup(t_shell *shell, t_fork *frk);
void	handle_exec_child(t_shell *shell, t_exec *exec_node, t_fork *frk);
void	handle_builtin_child(t_shell *shell, t_exec *exec_node, t_fork *frk);
void	exec_no_pipe_child(t_shell *shell, t_fork *frk);
void	execute_tree_recur(t_shell *shell, void *root,
			t_fork *frk, int pipe_index);

// ----------Fork----------
void	handle_fork(t_shell *shell, t_fork *frk, int pipe_index);
void	aux_fork(pid_t pid);

// ----------Checks----------
void	check_bt(t_shell *shell, t_exec *exec_node, t_fork *frk);
int		find_executable(t_shell *shell, t_exec *exec_node, char *command);
