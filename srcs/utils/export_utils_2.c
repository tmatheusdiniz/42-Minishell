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

 void	set_only_key(char *key, t_env_v *env_v)
{
	t_env_v	*new_node;

	if (!key || !env_v)
		return ;
	while (env_v->next)
	{
		if (env_v->KEY && ft_strcmp(env_v->KEY, key) == 0)
			return ;
		env_v = env_v->next;
	}
	new_node = create_node(key, NULL);
	if (!new_node)
		return ;
			env_v->next = new_node;;
	env_v->next = new_node;
}
