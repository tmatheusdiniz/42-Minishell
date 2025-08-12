/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:50:43 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/25 23:51:30 by alberto          ###   ########.fr       */
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

bool	expand_check(char *input)
{
	int	len;
	int	i;

	if (!input || !input[0])
		return (false);
	len = ft_strlen(input);
	if (len >= 2 && input[0] == '\'' && input[len - 1] == '\'')
	{
		i = 1;
		while (i < len - 1)
		{
			if (input[i] == '\'' || input[i] == '"')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

char	*aux_handle_exit_expand(char *string, int *inc)
{
	char	*temp;
	int		c;

	c = 0;
	temp = handle_exit_status(inc);
	if (!temp)
		return (NULL);
	while (temp[c])
	{
		string[inc[1]] = temp[c];
		inc[1]++;
		c++;
	}
	free(temp);
	return (string);
}

char	*aux_handle_literal_dollar(int *inc, char *input, char *env_var)
{
	char	quote;

	quote = input[inc[0]];
	inc[0]++;
	while (input[inc[0]] && input[inc[0]] != quote)
		inc[0]++;
	if (input[inc[0]] == quote)
		inc[0]++;
	env_var[0] = '\0';
	return (ft_strdup(env_var));
}
