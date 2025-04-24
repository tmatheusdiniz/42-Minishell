/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:43:21 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/24 18:59:51 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe_node(t_token *pipe_token)
{
	t_pipe	*pipe;
	
	if (!pipe_token)
		return (NULL);
	pipe = (t_pipe *)ft_calloc(sizeof(t_pipe), 1);
	pipe->type = pipe->type;
	pipe->left = NULL;
	pipe->right = NULL;
	return (pipe);	
}

bool	*search_pipe(t_token *token)
{
	t_token *cur;
	
	if (!token)
		return (false);
	cur = token;
	while(cur->type != PIPE)
		cur = cur->next;
	if (cur->type == PIPE)
		create_pipe(cur);
}

t_mini	*build_tree(t_mini *mini, char *start)
{
	if (search_pipe(mini->tokens))
		return ;
}