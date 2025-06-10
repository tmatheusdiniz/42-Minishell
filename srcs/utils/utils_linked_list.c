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
