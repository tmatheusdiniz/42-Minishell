/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:34:47 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 18:41:32 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_outredir(void *root)
{
	t_outredir	*redir;

	redir = (t_outredir *)root;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_tree(redir->next);
}

void	free_inredir(void *root)
{
	t_inredir	*redir;

	redir = (t_inredir *)root;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_tree(redir->next);
}

void	free_append(void *root)
{
	t_append	*redir;

	redir = (t_append *)root;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_tree(redir->next);
}

void	free_heredoc(void *root)
{
	t_heredoc	*redir;

	redir = (t_heredoc *)root;
	if (redir->delimiter)
		free(redir->delimiter);
	if (redir->content)
		free(redir->content);
	if (redir->next)
		free_tree(redir->next);
}
