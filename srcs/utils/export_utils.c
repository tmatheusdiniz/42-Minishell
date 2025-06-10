/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:34 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/26 21:27:30 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>

static void	aux_sort_linked_l(t_env_v *env_v,
		int *j, int *flag, int linked_size)
{
	t_env_v	*current;
	char	*save_key;
	char	*save_value;

	current = env_v;
	while (*j < linked_size && current && current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			*flag = 1;
			save_key = current->key;
			save_value = current->value;
			current->key = current->next->key;
			current->value = current->next->value;
			current->next->key = save_key;
			current->next->value = save_value;
		}
		current = current->next;
		(*j)++;
	}
}

void	ft_sort_linked(t_env_v *env_v)
{
	int		i;
	int		j;
	int		flag;
	int		linked_size;

	i = 1;
	j = 1;
	flag = 0;
	linked_size = linked_env_size(env_v);
	while (i < linked_size)
	{
		j = 1;
		aux_sort_linked_l(env_v, &j, &flag, linked_size);
		if (!flag)
			break ;
		flag = 0;
		i ++;
	}
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
	new_node = create_node(key, NULL);
	if (!new_node)
		return (NULL);
	position = find_position(env_v, key, linked_env_size(env_v));
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

// I had to create this function for
// case which the var has a value with "=" inside.
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

t_env_v	*envp_to_linked_l(char **envp)
{
	int		i;
	t_env_v	*head;
	t_env_v	*current;
	t_env_v	*new_node;
	char	**save;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		save = aux_set(envp[i++]);
		if (!save)
			return (NULL);
		new_node = create_node(save[0], save[1]);
		clean_matrix(save);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return (head);
}
