/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/01 00:01:53 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**duplicate_env_v(char **envp)
{
	char	**duplicate;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	duplicate = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		duplicate[i] = ft_strdup(envp[i]);
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

char	*check_space(char *input)
{
	int	i;

	if (!input)
		return (NULL);
	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	return (&input[i]);
}

int	get_index_env_parsing(t_shell *mini, char *var)
{
	char	*clean_var;
	int		len;
	int		i;

	i = 0;
	clean_var = clean_other_chars(var);
	len = ft_strlen(clean_var);
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], clean_var, len) == 0 && mini->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i ++;
	return (s1[i] - s2[i]);
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

int	check_command(t_shell *shell, char **input)
{
	if (!ft_strncmp(input[0], "cd", ft_strlen(input[0])))
		ft_cd(shell->env_v, input);
	else if (!ft_strncmp(input[0], "pwd", ft_strlen(input[0])))
		ft_pwd();
	else if (!ft_strncmp(input[0], "echo", ft_strlen(input[0])))
		ft_echo(input);
	else if (!ft_strncmp(input[0], "env", ft_strlen(input[0])))
	{
		if (input[1])
		{
			ft_printf("env: '%s': No such file or directory\n", input[1]);
			return (-1);
		}
		else
			ft_env(shell->envp);
	}
	else if (!ft_strncmp(input[0], "unset", ft_strlen(input[0])))
		ft_unset(shell->env_v, input[1]);
	else if (!(ft_strncmp(input[0], "export", ft_strlen(input[0]))))
		ft_export(shell->env_v, input[1]);
	else if (!check_exec(input[0]))
		printf("Exec\n");
	else
		ft_printf("%s: command not found\n", input[0]);
	return (0);
}