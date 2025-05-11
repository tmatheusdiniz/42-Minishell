/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/11 16:37:15 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index_env(t_mini *mini, char *var)
{
	char	*clean_var;
	int		len;
	int		i;

	i = 0;
	clean_var = clean_other_chars(var);
	len = ft_strlen(clean_var);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], clean_var, len) == 0 && mini->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*check_space(char *input)
{
	int	i;

	i = 0;
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
	{
		i++;
	}
	return (&input[i]);
}

bool	check_exec(char *token)
{
	char	**splitted_path;
	char	*path;
	char	*the_return_of_spplited_path;

	splitted_path = ft_split(getenv("PATH"), ':');
	path = ft_strjoin(splitted_path[6], "/");
	free(splitted_path);
	the_return_of_spplited_path = ft_strjoin(path, token);
	if (access(the_return_of_spplited_path, X_OK))
	{
		free(the_return_of_spplited_path);
		free(path);
		return (true);
	}
	free(the_return_of_spplited_path);
	free(path);
	return (false);
}

bool	check_builtin(char *token)
{
	if (!ft_strncmp(token, "cd", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "pwd", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "echo", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "env", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "unset", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "export", ft_strlen(token)))
		return (true);
	else if (!ft_strncmp(token, "exit", ft_strlen(token)))
		return (true);
	else
		return (false);
}

int	match_type(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (PIPE);
	else if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (INREDIR);
	else if (!ft_strncmp(token, "<<", ft_strlen(token)))
		return (HEREDOC);
	else if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (OUTREDIR);
	else if (!ft_strncmp(token, ">>", ft_strlen(token)))
		return (APPEND);
	else if (check_builtin(token))
		return (CMD);
	else if (!check_exec(token))
		return (EXEC);
	else
		return (ARG);
}
