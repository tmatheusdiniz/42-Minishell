/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:31:44 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 16:38:51 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*create_inredir(t_token *right_tokens, void *next_node);
void	*create_append(t_token *right_tokens, void *next_node);
void	*create_heredoc(t_token *right_tokens, void *next_node);

void	*create_outredir(t_token *right_tokens, void *next_node)
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
	return (redir);
}

void	*create_inredir(t_token *right_tokens, void *next_node)
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
	return (redir);
}

void	*create_append(t_token *right_tokens, void *next_node)
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
	return (redir);
}

void	*create_heredoc(t_token *right_tokens, void *next_node)
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
	return (redir);
}

void	*create_redir_node(t_token *redir_token, t_token *right_tokens,
		t_token *left_tokens)
{
	t_token	*file_token;
	t_token	*remaining_tokens;
	t_token	*recombined_list;
	t_token	*tail;

	if (!right_tokens)
		return (NULL);
	file_token = right_tokens;
	remaining_tokens = right_tokens->next;
	file_token->next = NULL;
	if (remaining_tokens)
		remaining_tokens->prev = NULL;
	if (left_tokens)
	{
		tail = left_tokens;
		while (tail && tail->next)
			tail = tail->next;
		tail->next = remaining_tokens;
		if (remaining_tokens)
			remaining_tokens->prev = tail;
		recombined_list = left_tokens;
	}
	else
		recombined_list = remaining_tokens;
	return (aux_redir_node(redir_token, file_token, recombined_list));
}
