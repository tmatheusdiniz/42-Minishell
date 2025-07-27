/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:01:48 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/19 16:25:18 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <minishell.h>
#include <stdlib.h>

static void		print_all_var(t_env_v *env_v);
static t_env_v	*key_and_value(t_shell *shell, t_env_v *env_v, char *arg);
static t_env_v	*aux_key_value(t_env_v *env_v, t_env_v *new_node, int position);

static void	parse_of_arguments(t_shell *shell, char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		if (!(ft_strchr(arguments[i], '=')))
		{
			if (check_duplicated(shell, shell->env_v, arguments[i], 0))
				continue ;
			else
				shell->env_v = set_only_key(shell->env_v, arguments[i]);
		}
		else
		{
			if (check_duplicated(shell, shell->env_v, arguments[i], 1))
			{
				if (modify_value_env(shell->env_v, arguments[i]))
					malloc_failure(shell, "parse_of_arguments");
			}
			else
				shell->env_v = key_and_value(shell, shell->env_v, arguments[i]);
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

static t_env_v	*key_and_value(t_shell *shell, t_env_v *env_v, char *arg)
{
	int		position;
	char	*value;
	char	**matrix;
	t_env_v	*new_node;

	matrix = ft_split(arg, '=');
	if (!matrix || !matrix[0])
		return (NULL);
	value = ft_strchr(arg, '=');
	new_node = create_node(matrix[0], value + 1);
	if (!new_node)
		return (NULL);
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
