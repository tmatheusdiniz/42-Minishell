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

#include "../../include/minishell.h"

static void	aux_sorted_l(t_env_v *env_v, int *j, int *flag, int linked_size);

int	count_linked_list(t_env_v *list)
{
	int	i;

	i = 1;
	while (list->next)
	{
		i ++;
		list = list->next;
	}
	return (i);
}

static void	aux_sorted_l(t_env_v *env_v, int *j, int *flag, int linked_size)
{
	t_env_v	*current;
	char	*save_key;
	char	*save_value;

	current = env_v;
	while (*j < linked_size && current && current->next)
	{
		if (ft_strcmp(current->KEY, current->next->KEY) > 0)
		{
			*flag = 1;
			save_key = current->KEY;
			save_value = current->VALUE;
			current->KEY = current->next->KEY;
			current->VALUE = current->next->VALUE;
			current->next->KEY = save_key;
			current->next->VALUE = save_value;
		}
		current = current->next;
		(*j)++;
	}
}

void	ft_sort_linked(t_env_v *env_v, int linked_size)
{
	int		i;
	int		j;
	int		flag;

	i = 1;
	j = 1;
	flag = 0;
	linked_size = count_linked_list(env_v);
	while (i < linked_size)
	{
		j = 1;
		aux_sorted_l(env_v, &j, &flag, linked_size);
		if (!flag)
			break ;
		flag = 0;
		i ++;
	}
}

void	*create_node(char *key_name, char *content)
{
	t_env_v	*env_v;

	if (!key_name)
		return (NULL);
	env_v = (t_env_v *)malloc(sizeof(t_env_v));
	if (!env_v)
		return (NULL);
	env_v->KEY = ft_strdup(key_name);
	if (!env_v->KEY)
		return (free(env_v), NULL);
	if (!content)
		env_v->VALUE = NULL;
	else
		env_v->VALUE = ft_strdup(content);
	env_v->next = NULL;
	return (env_v);
}

void	*envp_to_l_l(char **envp)
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
	return ((t_env_v *)head);
}
