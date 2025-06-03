/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:50:43 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/03 21:02:40 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* int	get_index_env_parsing(t_shell *mini, char *var)
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
*/
t_env	*get_env_node_parsing(t_shell *mini, char *var)
{
	char	*clean_var;
	int		len;
	t_env *current;

	if (!mini || !var || !mini->env_v)
		return (NULL);
	clean_var = clean_other_chars(var);
	if (!clean_var)
		return (NULL);
	len = ft_strlen(clean_var);
	current = mini->env_v;
	while (current)
	{
		if (current->key && ft_strncmp(current->key, clean_var, len) == 0
				&& (current->key[len] == '\0' || current->key[len] == '='))
		{
			free(clean_var);
			return (current);
		}
		current = current->next;
    }
	free(clean_var);
	return (NULL);
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
		printf("Exec\n"); // temporary
	else
		ft_printf("%s: command not found\n", input[0]);
	return (0);
}
