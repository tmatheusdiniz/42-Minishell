/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:49:39 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/28 23:25:11 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_position(t_env_v *env_v, char *new_key, int linked_size)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	linked_size = count_linked_list(env_v);
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

static int	check_duplicated(t_env_v *current, char *key)
{
	while (current->next)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

 t_env_v	*set_only_key(t_env_v *env_v, char *key)
{
	t_env_v	*new_node;
	t_env_v	*head;
	t_env_v	*save;
	int		position;
	int		i;

	if (!key || !env_v)
		return (NULL);
	if (check_duplicated(env_v, key))
		return (NULL);
	new_node = create_node(key, NULL);
	if (!new_node)
		return (NULL);
	position = find_position(env_v, key, count_linked_list(env_v));
	if (position == 0)
		return (new_node->next = env_v, new_node);
	i = 1;
	head = env_v;
	while (i++ < position && env_v)
		env_v = env_v->next;
	save = env_v->next;
	env_v->next = new_node;
	new_node->next = save;
	return (head);
}

// I had to create this function for case which the var has a value with "=" inside.
// e.g.: TEST="xx=1 , yy=1"

char	**aux_set(char *envp)
{
	char	**save;
	char	*temp;

	save = ft_split(envp, '=');
	if (!save)
		return (NULL);
	if (save[2])
	{
		temp = ft_strdup(save[0]);
		clean_matrix(save);
		save = malloc(sizeof(char *) * 3);
		if (!save)
			return (NULL);
		save[0] = temp;
		temp = ft_strchr(envp, '=');
		temp ++;
		save[1] = ft_strdup(temp);
		save[2] = NULL;
	}
	return (save);
}
