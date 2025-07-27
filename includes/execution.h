/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:23:56 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/27 10:07:13 by alberto          ###   ########.fr       */
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
int		exec_outredir(t_shell *shell, void *root);
int		exec_inredir(t_shell *shell, void *root);
int		exec_append(t_shell *shell, void *root);
int		exec_heredoc(t_shell *shell, void *root);
void	read_all_heredocs(void *root);
void	read_all_heredocs_with_shell(void *root, t_shell *shell);

// ----------Utils Execute----------
void	aux_execute(t_shell *shell);
void	aux_execution(t_shell *shell, void *root);

// ----------Utils Pipe----------
t_fork	*handle_pipe(t_shell *shell, void *root);
bool	check_pipe_rgt(void	*root);
int		count_pipes(void *root);
void	set_pipe(t_fork *frk, int pipe_index);

// ----------Utils Execute----------
void	check_lastcmd(t_shell *shell, void *root,
			t_fork *frk, int pipe_index);

// ----------Fork----------
void	handle_fork(t_shell *shell, t_fork *frk, int pipe_index);

// ----------Checks----------
void	check_bt(t_shell *shell, t_exec *exec_node);
int		find_executable(t_shell *shell, t_exec *exec_node, char *command);
