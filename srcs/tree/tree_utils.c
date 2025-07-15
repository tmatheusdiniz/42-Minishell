/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:31:44 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/15 11:57:32 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	*create_inredir(t_token *right_tokens, void *next_node);
static void	*create_append(t_token *right_tokens, void *next_node);
static void	*create_heredoc(t_token *right_tokens, void *next_node);

static void	*create_outredir(t_token *right_tokens, void *next_node)
{
	t_outredir	*redir;

	redir = ft_calloc(sizeof(t_outredir), 1);
	if (!redir)
		return (NULL);
	redir->type = OUTREDIR;
	if (right_tokens)
		redir->file = ft_strdup(right_tokens->token);
	else
		redir->file = NULL;
	redir->next = next_node;
	free_right_tokens(right_tokens);
	return (redir);
}

static void	*create_inredir(t_token *right_tokens, void *next_node)
{
	t_inredir	*redir;

	redir = ft_calloc(sizeof(t_inredir), 1);
	if (!redir)
		return (NULL);
	redir->type = INREDIR;
	if (right_tokens)
		redir->file = ft_strdup(right_tokens->token);
	else
		redir->file = NULL;
	redir->next = next_node;
	free_right_tokens(right_tokens);
	return (redir);
}

static void	*create_append(t_token *right_tokens, void *next_node)
{
	t_append	*redir;

	redir = ft_calloc(sizeof(t_append), 1);
	if (!redir)
		return (NULL);
	redir->type = APPEND;
	if (right_tokens)
		redir->file = ft_strdup(right_tokens->token);
	else
		redir->file = NULL;
	redir->next = next_node;
	free_right_tokens(right_tokens);
	return (redir);
}

static void	*create_heredoc(t_token *right_tokens, void *next_node)
{
	t_heredoc	*redir;

	redir = ft_calloc(sizeof(t_heredoc), 1);
	if (!redir)
		return (NULL);
	redir->type = HEREDOC;
	if (right_tokens)
		redir->delimiter = ft_strdup(right_tokens->token);
	else
		redir->delimiter = NULL;
	redir->next = next_node;
	redir->content = NULL;
	free_right_tokens(right_tokens);
	return (redir);
}

/* void	*create_redir_node(t_token *redir_token, t_token *right_tokens, t_token *left_tokens)
{
	void	*next_node;

	next_node = build_tree(left_tokens);
	if (redir_token->type == OUTREDIR)
		return (create_outredir(right_tokens, next_node));
	else if (redir_token->type == INREDIR)
		return (create_inredir(right_tokens, next_node));
	else if (redir_token->type == APPEND)
		return (create_append(right_tokens, next_node));
	else if (redir_token->type == HEREDOC)
		return (create_heredoc(right_tokens, next_node));
	return (NULL);
} */

void	*create_redir_node(t_token *redir_token, t_token *right_tokens,
		t_token *left_tokens)
{
	void	*next_node;
	t_token	*file_token;
	t_token	*remaining_tokens;
	t_token	*recombined_list;

	if (!right_tokens)
		return (NULL);
	file_token = right_tokens;
	remaining_tokens = right_tokens->next;
	file_token->next = NULL;
	if (remaining_tokens)
		remaining_tokens->prev = NULL;
	if (left_tokens)
	{
		t_token	*tail = left_tokens;
		while (tail && tail->next)
			tail = tail->next;
		tail->next = remaining_tokens;
		if (remaining_tokens)
			remaining_tokens->prev = tail;
		recombined_list = left_tokens;
	}
	else
		recombined_list = remaining_tokens;
	next_node = build_tree(recombined_list);
	if (redir_token->type == OUTREDIR)
		return (create_outredir(file_token, next_node));
	else if (redir_token->type == INREDIR)
		return (create_inredir(file_token, next_node));
	else if (redir_token->type == APPEND)
		return (create_append(file_token, next_node));
	else if (redir_token->type == HEREDOC)
		return (create_heredoc(file_token, next_node));
	return (NULL);
}
