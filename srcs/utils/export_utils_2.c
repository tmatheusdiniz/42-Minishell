/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:49:39 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/28 21:04:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"
#include <minishell.h>

static void	update_envp(t_shell *shell, char *key)
{
	int		i;
	int		flag;
	char	**splt;

	i = 0;
	flag = 0;
	splt = ft_split(key, '=');
	if (!splt)
		malloc_failure(shell, "update_envp");
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], splt[0], ft_strlen(splt[0])))
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(key);
			if (!shell->envp[i])
				malloc_failure(shell, "key");
			flag = 1;
		}
		i++;
	}
	if (!flag)
		add_var_envp(shell, splt[0], ft_strchr(key, '='));
	clean_matrix(splt);
}

int	update_value(t_shell *shell, t_env_v *env_v, char *argument)
{
	char	**splt;

	splt = ft_split(argument, '=');
	if (!splt)
		return (-1);
	while (env_v)
	{
		if (!ft_strcmp(env_v->key, splt[0]))
		{
			if (env_v->value)
				free (env_v->value);
			if (!splt[1] || splt[1][0] == '\0')
				env_v->value = ft_strdup("");
			else
				env_v->value = ft_strdup(splt[1]);
			if (!env_v->value)
				return (clean_matrix(splt), -1);
			break ;
		}
		env_v = env_v->next;
	}
	if (argument)
		update_envp(shell, argument);
	return (clean_matrix(splt), 0);
}

int	find_position(t_env_v *env_v, char *new_key, int linked_size)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	linked_size = linked_env_size(env_v);
	while (i < linked_size && env_v)
	{
		if (ft_strcmp(env_v->key, new_key) < 0)
			count++;
		else
			return (count);
		env_v = env_v->next;
	}
	return (count);
}

int	check_duplicated(t_shell *shell, t_env_v *current, char *key)
{
	char	**matrix;
	char	*equal_sign;

	equal_sign = ft_strchr(key, '=');
	matrix = NULL;
	if (equal_sign && equal_sign != key)
	{
		matrix = ft_split(key, '=');
		if (!matrix || !matrix[0])
			malloc_failure(shell, "check_duplicated");
		key = matrix[0];
	}
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			if (matrix)
				clean_matrix(matrix);
			return (1);
		}
		current = current->next;
	}
	if (matrix)
		clean_matrix(matrix);
	return (0);
}

int	check_append(char *key)
{
	int		i;

	i = 0;
	while (key[i])
	{
		if (key[i] && key[i] == '=' && ft_strlen(key) > 1)
		{
			if (key[i - 1] == '+')
				return (1);
			else
				break ;
		}
		i++;
	}
	return (0);
}
