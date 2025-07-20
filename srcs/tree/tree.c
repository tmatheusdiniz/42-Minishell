/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:43:21 by cda-fons          #+#    #+#             */
/*   Updated: 2025/07/21 00:40:49 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cut_tokens(t_token *tokens, t_token *base, t_token **left_tokens,
		t_token **right_tokens)
{
	*right_tokens = base->next;
	if (*right_tokens)
		(*right_tokens)->prev = NULL;
	if (base->prev)
	{
		base->prev->next = NULL;
		*left_tokens = tokens;
	}
	else
		*left_tokens = NULL;
	base->next = NULL;
	base->prev = NULL;
}

t_token	*search_pipe(t_token *token)
{
	t_token	*pipe;

	pipe = token;
	while (pipe)
	{
		if (pipe->type == PIPE)
			return (pipe);
		pipe = pipe->next;
	}
	return (NULL);
}

t_token	*search_redir(t_token *token)
{
	t_token	*cur;
	t_token	*redir;

	redir = NULL;
	cur = token;
	while (cur)
	{
		if (cur->type == OUTREDIR
			|| cur->type == INREDIR
			|| cur->type == APPEND
			|| cur->type == HEREDOC)
		{
			redir = cur;
			return (redir);
		}
		cur = cur->next;
	}
	return (redir);
}

void	*build_tree(t_token *tokens)
{
	t_token	*pipe;
	t_token	*left_tokens;
	t_token	*right_tokens;
	t_token	*redir;

	if (!tokens)
		return (NULL);
	pipe = search_pipe(tokens);
	if (pipe)
	{
		right_tokens = NULL;
		left_tokens = NULL;
		cut_tokens(tokens, pipe, &left_tokens, &right_tokens);
		return (create_pipe_node(left_tokens, right_tokens));
	}
	redir = search_redir(tokens);
	if (redir)
	{
		right_tokens = NULL;
		left_tokens = NULL;
		cut_tokens(tokens, redir, &left_tokens, &right_tokens);
		return (create_redir_node(redir, right_tokens, left_tokens));
	}
	return (create_exec_node(tokens, 0));
}
