/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/21 18:52:23 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index_env(t_mini *mini, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(var);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var, len) == 0 && mini->env[i][len] == '=')
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
	else
		return (EXEC);
}