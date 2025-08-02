/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:34 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/27 12:11:07 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "errors.h"
#include <minishell.h>
#include <stdlib.h>

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

char	**aux_set(char *envp)
{
	char	**save;
	char	*temp;
	int		i;

	save = ft_split(envp, '=');
	if (!save)
		return (NULL);
	i = 0;
	while (save[i])
		i++;
	if (i > 2)
	{
		temp = ft_strchr(envp, '=');
		if (temp)
		{
			temp++;
			i = 1;
			while (save[i])
				free(save[i++]);
			save[1] = ft_strdup(temp);
			save[2] = NULL;
		}
	}
	return (save);
}

void	set_with_append(t_shell *shell, t_env_v *current, char *key)
{
	char	**splt;
	char	*old_value;

	splt = ft_split(key, '+');
	if (check_duplicated(shell, shell->env_v, splt[0]))
	{
		while (current)
		{
			if (current->key && ft_strcmp(current->key, splt[0]) == 0)
			{
				(splt[1])++;
				old_value = ft_strdup(current->value);
				current->value = ft_strjoin(current->value, splt[1]);
				if (!old_value || !current->value)
					malloc_failure(shell, "set_with_append");
				update_envp_append(shell, ft_strjoin(splt[0],
						ft_strjoin("=", old_value)), splt[1]);
			}
			current = current->next;
		}
	}
	else
		key_and_value(shell, shell->env_v, ft_strjoin(splt[0], splt[1]));
	if (splt && splt[0])
		clean_matrix(splt);
}
