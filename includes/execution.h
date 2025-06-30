/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:23:56 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/15 20:28:06 by mreinald         ###   ########.fr       */
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
