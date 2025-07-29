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
#include "utils.h"
#include <minishell.h>

int	modify_value_env(t_env_v *env_v, char *argument)
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

int	check_duplicated(t_shell *shell, t_env_v *current, char *key, int flag)
{
	char	**matrix;
	char	*equal_sign;

	equal_sign = ft_strchr(key, '=');
	matrix = NULL;
	if (equal_sign && equal_sign != key)
	{
		if (flag)
		{
			matrix = ft_split(key, '=');
			if (!matrix || !matrix[0])
				malloc_failure(shell, "check_duplicated");
			key = matrix[0];
		}
	}
	else
	{
		ft_putstr("minishell: export: '");
		ft_putstr(key);
		ft_putendl_fd("': not a valid identifier", 1);
		return (0);
	}
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	if (matrix)
		clean_matrix(matrix);
	return (0);
}

void	*create_node(char *key_name, char *content)
{
	t_env_v	*env_v;

	if (!key_name)
		return (NULL);
	env_v = (t_env_v *)malloc(sizeof(t_env_v));
	if (!env_v)
		return (NULL);
	env_v->key = ft_strdup(key_name);
	if (!env_v->key)
		return (free(env_v), NULL);
	if (!content)
		env_v->value = NULL;
	else
		env_v->value = ft_strdup(content);
	env_v->next = NULL;
	return (env_v);
}
int	validate_and_process_with_equal(t_shell *shell, char *arg)
{
	char	**temp_split;

	temp_split = ft_split(arg, '=');
	if (!temp_split || !temp_split[0] || !is_valid_identifier(temp_split[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		if (temp_split)
			clean_matrix(temp_split);
		return (0);
	}
	clean_matrix(temp_split);
	if (check_duplicated(shell, shell->env_v, arg, 1))
	{
		if (modify_value_env(shell->env_v, arg))
			malloc_failure(shell, "parse_of_arguments");
	}
	else
		shell->env_v = key_and_value(shell, shell->env_v, arg);
	return (1);
}