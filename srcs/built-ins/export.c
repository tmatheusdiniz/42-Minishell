/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:01:48 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/18 18:54:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		print_all_var(t_env_v *env_v);
static t_env_v	*key_and_value(t_env_v *env_v, char *arg);
static t_env_v	*aux_key_value(t_env_v *env_v, t_env_v *new_node, int position);

static void	parse_of_arguments(t_env_v *env_v, char *argument)
{
	if (!(ft_strchr(argument, '=')))
		env_v = set_only_key(env_v, argument);
	else
		env_v = key_and_value(env_v, argument);
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

static t_env_v	*key_and_value(t_env_v *env_v, char *arg)
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
	clean_matrix(matrix);
	position = find_position(env_v, matrix[0], count_linked_list(env_v));
	if (position == 0)
		return (new_node->next = env_v, new_node);
	env_v = aux_key_value(env_v, new_node, position);
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

void	ft_export(t_env_v *env_v, char *argument)
{
	if (!argument)
		print_all_var(env_v);
	else
		parse_of_arguments(env_v, argument);
}
