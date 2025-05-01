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

static int	find_position(t_env_v *env_v, int linked_size)
{
	int		i;
	int		count;

	i = 1;
	count = 1;
	linked_size = count_linked_list(env_v);
	while (i < linked_size && env_v)
	{
		if (ft_strcmp(env_v->KEY, env_v->next->KEY) > 0)
			count++;
		else
			return (count);
		env_v = env_v->next;
	}
	return (count);
}

 void	set_only_key(char *key, t_env_v *env_v)
{
	t_env_v	*new_node;
	t_env_v	*current;
	t_env_v	*save;
	int		position;
	int		i;

	if (!key || !env_v)
		return ;
	current = env_v;
	while (current->next)
	{
		if (current->KEY && ft_strcmp(current->KEY, key) == 0)
			return ;
		current = current->next;
	}
	new_node = create_node(key, NULL);
	if (!new_node)
		return ;
	position = find_position(env_v, count_linked_list(env_v));
	i = 1;
	while (i++ < position && current)
		env_v = env_v->next;
	save = env_v->next;
	env_v->next = new_node;
	new_node->next = save;
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
