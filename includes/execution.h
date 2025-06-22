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

void	ft_execution(t_shell *shell, t_exec *exec_node);

// Utils

int		check_pipe_lft(void *root);
bool	check_pipe_rgt(void	*root);
int		count_pipes(void *root);

