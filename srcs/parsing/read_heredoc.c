/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:49:42 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/29 18:54:07 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_quotes(char *delimiter)
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

char	*remove_delimiter_quotes(char *delimiter)
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

void	read_all_heredocs(void *root)
{
	read_all_heredocs_with_shell(root, NULL);
}

void	aux_heredoc_content(char *line, char *delimiter, int free_delim)
{
	if (line)
		free(line);
	if (free_delim)
		free(delimiter);
}
