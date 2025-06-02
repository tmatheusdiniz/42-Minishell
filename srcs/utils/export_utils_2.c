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

#include <minishell.h>

int	find_position(t_env_v *env_v, char *new_key, int linked_size)
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

int	check_duplicated(t_env_v *current, char *key)
{
	while (current->next)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
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
