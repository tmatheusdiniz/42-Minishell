/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:20:44 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/27 21:20:49 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*clean_delimiter(t_heredoc *heredoc, int *should_free)
{
	char	*clean;

	*should_free = 0;
	clean = remove_delimiter_quotes(heredoc->delimiter);
	if (!clean)
		return (heredoc->delimiter);
	if (clean != heredoc->delimiter)
		*should_free = 1;
	return (clean);
}

static char	*process_heredoc_line(char *line, int expd,
		t_shell *shell, char *content)
{
	char	*expanded;
	char	*tmp;
	char	*new_content;

	expanded = line;
	if (expd && shell)
	{
		expanded = expand(line, shell);
		if (!expanded)
			expanded = line;
	}
	if (content)
	{
		tmp = ft_strjoin(content, expanded);
		free(content);
		new_content = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	else
		new_content = ft_strjoin(expanded, "\n");
	if (expanded != line)
		free(expanded);
	return (new_content);
}

static char	*read_heredoc_content(t_heredoc *heredoc, t_shell *shell)
{
	char	*line;
	char	*content;
	char	*delimiter;
	int		should_expand;
	int		free_delim;

	should_expand = !has_quotes(heredoc->delimiter);
	delimiter = clean_delimiter(heredoc, &free_delim);
	content = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		content = process_heredoc_line(line, should_expand, shell, content);
		free(line);
	}
	if (line)
		free(line);
	if (free_delim)
		free(delimiter);
	return (content);
}

void	aux_read_hd(void *root, t_shell *shell)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)root;
	heredoc->content = read_heredoc_content(heredoc, shell);
	read_all_heredocs_with_shell(heredoc->next, shell);
}
