/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:50:43 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/11 21:40:01 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env_v	*get_env_node_parsing(t_shell *mini, char *var, t_env_v	*current)
{
	char	*clean_var;
	int		len;

	if (!mini || !var || !mini->env_v)
		return (NULL);
	clean_var = clean_other_chars(var);
	if (!clean_var)
		return (NULL);
	len = ft_strlen(clean_var);
	current = mini->env_v;
	while (current)
	{
		if (current->key && !ft_strncmp(current->key, clean_var, len))
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
		return (BT);
	else if (!check_if_exec(token))
		return (EXEC);
	else
		return (EXEC);
}

int	check_command(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node)
		malloc_failure(shell, "check_command");
	if (!ft_strncmp(exec_node->argv[0], "cd",
			ft_strlen(exec_node->argv[0])))
		ft_cd(shell, exec_node);
	else if (!ft_strncmp(exec_node->argv[0],
			"pwd", ft_strlen(exec_node->argv[0])))
		ft_pwd();
	else if (!ft_strncmp(exec_node->argv[0], "echo",
			ft_strlen(exec_node->argv[0])))
		ft_echo(exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "env",
			ft_strlen(exec_node->argv[0])))
		ft_env(shell->envp, exec_node->argv);
	else if (!ft_strncmp(exec_node->argv[0], "unset",
			ft_strlen(exec_node->argv[0])))
		ft_unset(shell, exec_node->argv + 1);
	else if (!(ft_strncmp(exec_node->argv[0], "export",
				ft_strlen(exec_node->argv[0]))))
		ft_export(shell, exec_node->argv);
	else if (!(ft_strncmp(exec_node->argv[0], "exit",
				ft_strlen(exec_node->argv[0]))))
		ft_exit(shell, exec_node);
	else if (!check_if_exec(exec_node->argv[0]))
		ft_execution(shell);
	else
	{
		ft_putstr_fd("%s: command not found: ", 2);
		ft_putendl_fd(exec_node->argv[0], 2);
	}
	return (0);
}

bool	expand_check(char *input)
{
	bool	d_flag;
	int		i;

	i = 0;
	d_flag = false;
	while (input[i])
	{
		if (input[i] && input[i] == '"')
			d_flag = true;
		if (input[i] && input[i] == '\'')
		{
			if (!d_flag)
				return (true);
			return (false);
		}
		i++;
	}
	return (false);
}
