/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:49:42 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/27 10:08:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_aux_read(t_heredoc *heredoc, char *content, char *line);

static int	has_quotes(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}	

static char	*remove_delimiter_quotes(char *delimiter)
{
	char	*clean;
	int		i;
	int		j;

	clean = malloc(ft_strlen(delimiter) + 1);
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '\'' && delimiter[i] != '"')
			clean[j++] = delimiter[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

static void	aux_read_hd(void *root, t_shell *shell)
{
	char		*line;
	char		*content;
	char		*tmp;
	char		*expanded_line;
	t_heredoc	*heredoc;
	char		*clean_delimiter;
	int			should_expand;

	heredoc = (t_heredoc *)root;
	content = NULL;
	should_expand = !has_quotes(heredoc->delimiter);
	clean_delimiter = remove_delimiter_quotes(heredoc->delimiter);
	if (!clean_delimiter)
		clean_delimiter = heredoc->delimiter;
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, clean_delimiter) == 0)
			break ;
		if (should_expand && shell)
		{
			expanded_line = expand(line, shell);
			if (!expanded_line)
				expanded_line = line;
		}
		else
			expanded_line = line;
		
		if (content)
		{
			tmp = ft_strjoin(content, expanded_line);
			free(content);
			content = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
			content = ft_strjoin(expanded_line, "\n");
		if (expanded_line != line)
			free(expanded_line);
		free(line);
	}
	if (line)
		free(line);
	if (clean_delimiter != heredoc->delimiter)
		free(clean_delimiter);
	heredoc->content = content;
	read_all_heredocs_with_shell(heredoc->next, shell);
}

void	read_all_heredocs_with_shell(void *root, t_shell *shell)
{
	t_outredir	*redir;
	t_pipe		*pipe;

	if (!root)
		return ;
	if (*(int *)root == PIPE)
	{
		pipe = (t_pipe *)root;
		read_all_heredocs_with_shell(pipe->left, shell);
		read_all_heredocs_with_shell(pipe->right, shell);
	}
	else if (*(int *)root == HEREDOC)
		aux_read_hd(root, shell);
	else if (*(int *)root == OUTREDIR || *(int *)root == INREDIR
		|| *(int *)root == APPEND)
	{
		redir = (t_outredir *)root;
		read_all_heredocs_with_shell(redir->next, shell);
	}
}

static void	aux_aux_read(t_heredoc *heredoc, char *content, char *line)
{
	heredoc->content = content;
	if (line)
		free (line);
}

void	read_all_heredocs(void *root)
{
	read_all_heredocs_with_shell(root, NULL);
}
