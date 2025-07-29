/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:01:48 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/28 21:03:12 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <minishell.h>
#include <stdlib.h>

static void		print_all_var(t_env_v *env_v);
static t_env_v	*aux_key_value(t_env_v *env_v, t_env_v *new_node, int position);

static void	parse_of_arguments(t_shell *shell, char **arguments)
{
	int		i;

	i = 0;
	while (arguments[i])
	{
		if (!(ft_strchr(arguments[i], '=')))
		{
			if (!is_valid_identifier(arguments[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(arguments[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				i++;
				continue;
			}
			if (check_duplicated(shell, shell->env_v, arguments[i], 0))
				continue ;
			else
				shell->env_v = set_only_key(shell->env_v, arguments[i]);
		}
		else
		{
			if (check_duplicated(shell, shell->env_v, arguments[i], 1))
				{
					i++;
					continue;
				}
		}
		++i;
	}
}

static t_env_v	*aux_key_value(t_env_v *env_v, t_env_v *new_node, int position)
{
	int		i;
	t_env_v	*head;
	t_env_v	*save;

	i = 1;
	head = env_v;
	while (i++ < position && env_v)
		env_v = env_v->next;
	save = env_v->next;
	env_v->next = new_node;
	new_node->next = save;
	return (head);
}

t_env_v	*key_and_value(t_shell *shell, t_env_v *env_v, char *arg)
{
	int		position;
	char	*value;
	char	**matrix;
	char	*new_var;
	t_env_v	*new_node;

	matrix = ft_split(arg, '=');
	if (!matrix || !matrix[0])
	{
		if (matrix)
			clean_matrix(matrix);
		return (env_v);
	}
	value = ft_strchr(arg, '=');
	new_node = create_node(matrix[0], value + 1);
	if (!new_node)
		return (clean_matrix(matrix), env_v);
	new_var = ft_strjoin(new_node->key, value);
	if (!new_var)
	{
		free(new_node->key);
		if (new_node->value)
			free(new_node->value);
		free(new_node);
		clean_matrix(matrix);
		return (env_v);
	}
	clean_matrix(matrix);
	position = find_position(env_v, new_node->key, linked_env_size(env_v));
	if (position == 0)
		return (new_node->next = env_v, new_node);
	env_v = aux_key_value(env_v, new_node, position);
	add_var_envp(shell, ft_strjoin(new_node->key, value));
	return (env_v);
}

static void	print_all_var(t_env_v *env_v)
{
	while (env_v)
	{
		if (env_v->value)
			ft_printf("declare -x %s=\"%s\"\n", env_v->key, env_v->value);
		else
			ft_printf("declare -x %s\n", env_v->key);
		env_v = env_v->next;
	}
}

void	ft_export(t_shell *shell, char **argv)
{
	ft_sort_linked(shell->env_v);
	if (!argv[1])
		print_all_var(shell->env_v);
	else
		parse_of_arguments(shell, argv + 1);
}