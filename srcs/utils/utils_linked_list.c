/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:29:49 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/04 20:30:04 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

t_env_v	*get_node_envp(t_env_v *env_v, char *KEY)
{
	while (env_v)
	{
		if (!(ft_strcmp(env_v->key, KEY)))
			return (env_v);
		env_v = env_v->next;
	}
	return (NULL);
}

int	get_index_env(t_env_v *env_v, char *var)
{
	int	i;

	i = 0;
	while (env_v)
	{
		if (ft_strcmp(env_v->key, var) == 0)
			return (i);
		i++;
		env_v = env_v->next;
	}
	return (-1);
}

int	linked_env_size(t_env_v *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i ++;
		list = list->next;
	}
	return (i);
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
