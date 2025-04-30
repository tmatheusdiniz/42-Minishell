/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:54:14 by alberto           #+#    #+#             */
/*   Updated: 2025/04/30 11:34:15 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens(t_token *tokens)
{
	int	count;
	t_token	*cur = tokens;

	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

void	*create_pipe_node(t_token *left_tokens, t_token *right_tokens)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)ft_calloc(sizeof(t_pipe), 1);
	if(!pipe)
		return NULL;
	pipe->type = PIPE;
	pipe->left = build_tree(left_tokens);
	pipe->right = NULL;
	return (pipe);	
}

void	*create_redir_node(t_token *redir_token, t_token *left_tokens,
			t_token *right_tokens)
{
	t_redir	*redir;
	t_token	*remaining;
		
	redir = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return NULL;
	redir->type = redir_token->type;
	redir->file = NULL;
	if (right_tokens)
		redir->file = ft_strdup(right_tokens->token);
	if (right_tokens && right_tokens->next)
	{
		remaining = right_tokens->next;
		remaining->next = NULL;
		redir->next = build_tree(remaining);
		free(right_tokens->token);
		free(right_tokens);
	}
	else
		redir->next = NULL;
	return (redir);	
}

void	*create_exec_node(t_token *exec_token)
{
	t_exec	*exec;
	t_token	*cur;
	int	args_count;
	int	i;
	
	exec = (t_exec *)ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		return (NULL);
	exec->type = exec_token->type;
	args_count = count_tokens(exec_token);
	exec->argv = (char **)ft_calloc(sizeof(char *), (args_count + 1));
	if (!exec->argv)
	{
		free(exec);
		return (NULL);
	}
	cur = exec_token;
	while (cur)
	{
		exec->argv[i] = ft_strdup(cur->token);
		i++;
		cur = cur->next;
	}
	exec->argv[i] = NULL;
	return (exec);
}

