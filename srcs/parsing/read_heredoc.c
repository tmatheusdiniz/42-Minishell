/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:49:42 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/25 23:17:54 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_read_hd(void *root)
{
	char		*line;
	char		*content;
	char		*tmp;
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)root;
	content = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, heredoc->delimiter) == 0)
			break ;
		if (content)
		{
			tmp = ft_strjoin(content, line);
			free(content);
			content = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
			content = ft_strjoin(line, "\n");
		free(line);
	}
	free(line);
	heredoc->content = content;
	read_all_heredocs(heredoc->next);
}

void	read_all_heredocs(void *root)
{
	t_outredir	*redir;
	t_pipe		*pipe;

	if (!root)
		return ;
	if (*(int *)root == PIPE)
	{
		pipe = (t_pipe *)root;
		read_all_heredocs(pipe->left);
		read_all_heredocs(pipe->right);
	}
	else if (*(int *)root == HEREDOC)
		aux_read_hd(root);
	else if (*(int *)root == OUTREDIR || *(int *)root == INREDIR
		|| *(int *)root == APPEND)
	{
		redir = (t_outredir *)root;
		read_all_heredocs(redir->next);
	}
}
