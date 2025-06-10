/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/09 19:00:16 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	aux_to_envp(char **envp)
{
	if (envp)
		clean_matrix(envp);
}

char	**linked_to_envp(t_shell *shell)
{
	int		i;
	int		len;
	char	**envp;
	char	*aux;
	t_env_v	*tmp;

	i = 0;
	len = linked_env_size(shell->env_v);
	tmp = shell->env_v;
	envp = (char **)ft_calloc(sizeof(char *), len + 1);
	while (tmp)
	{
		aux = ft_strjoin(tmp->key, "=");
		if (!aux)
			return (aux_to_envp(envp), NULL);
		envp[i] = ft_strjoin(aux, tmp->value);
		free (aux);
		if (!envp[i])
			return (aux_to_envp(envp), NULL);
		tmp = tmp->next;
		i ++;
	}
	return (envp);
}

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
		if (!duplicate[i])
		{
			while (--i >= 0)
				free (duplicate[i]);
			return (free (duplicate), NULL);
		}
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

char	*check_space(char *input)
{
	int	i;

	if (!input || !*input)
		return (NULL);
	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	return (&input[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i ++;
	return (s1[i] - s2[i]);
}
