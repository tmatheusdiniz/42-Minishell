/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:54:14 by alberto           #+#    #+#             */
/*   Updated: 2025/08/09 00:05:20 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_create_exec(t_exec *exec, t_token *exec_token, int *i);

int	count_tokens(t_token *tokens)
{
	t_token	*cur;
	int		count;

	cur = tokens;
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
	if (!pipe)
		return (NULL);
	pipe->type = PIPE;
	pipe->left = build_tree(left_tokens);
	pipe->right = build_tree(right_tokens);
	return (pipe);
}

static void	aux_create_exec(t_exec *exec, t_token *exec_token, int *i)
{
	t_token	*cur;

	cur = exec_token;
	while (cur)
	{
		exec->argv[*i] = ft_strdup(cur->token);
		(*i)++;
		cur = cur->next;
	}
}

void	*create_exec_node(t_token *exec_token, int i)
{
	t_exec	*exec;
	int		args_count;

	exec = (t_exec *)ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		return (NULL);
	exec->type = exec_token->type;
	args_count = count_tokens(exec_token);
	exec->argv = (char **)ft_calloc(sizeof(char *), (args_count + 1));
	if (!exec->argv)
		return (free(exec), NULL);
	aux_create_exec(exec, exec_token, &i);
	exec->argv[i] = NULL;
	return (exec);
}

void	*aux_redir_node(t_token *redir_token, t_token	*file_token,
		t_token	*recombined_list)
{
	void	*next_node;
	void	*redir_node;

	next_node = build_tree(recombined_list);
	if (redir_token->type == OUTREDIR)
		redir_node = create_outredir(file_token, next_node);
	else if (redir_token->type == INREDIR)
		redir_node = create_inredir(file_token, next_node);
	else if (redir_token->type == APPEND)
		redir_node = create_append(file_token, next_node);
	else if (redir_token->type == HEREDOC)
		redir_node = create_heredoc(file_token, next_node);
	else
		redir_node = NULL;
	return (redir_node);
}
