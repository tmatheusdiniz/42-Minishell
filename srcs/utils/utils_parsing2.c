/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:57:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/13 14:49:53 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*clean_other_chars(char *var)
{
	int		i;
	char	new_var[999];
	int		j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (ft_isalpha(var[i]))
			new_var[j++] = var[i++];
		else
			i++;
	}
	new_var[j] = '\0';
	return (ft_strdup(new_var));
}

char	*clean_quotes(char *var, int i, int j)
{
	char	new_var[999];
	bool	d_flag;
	bool	s_flag;

	d_flag = false;
	s_flag = false;
	while (var[i])
	{
		if (var[i] == '"' && !s_flag)
		{
			d_flag = !d_flag;
			i++;
		}
		else if (var[i] == '\'' && !d_flag)
		{
			s_flag = !s_flag;
			i++;
		}
		else
			new_var[j++] = var[i++];
	}
	new_var[j] = '\0';
	return (free(var), ft_strdup(new_var));
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

char	*check_env_var(char *input, int *inc)
{
	char	env_var[999];
	int		j;

	if (!input)
		return (NULL);
	j = 0;
	inc[0]++;
	while (input[inc[0]] && input[inc[0]] != ' ' && (input[inc[0]] != '"'
			&& input[inc[0]] != '\''))
	{
		env_var[j] = input[inc[0]];
		inc[0]++;
		j++;
	}
	env_var[j] = '\0';
	return (ft_strdup(env_var));
}
