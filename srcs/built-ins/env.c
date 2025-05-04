/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 20:25:19 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_env_v *env_v)
{
	int	i;

	i = 0;
	if (env_v)
		return (EXIT_FAILURE);	
	while (env_v)
	{
		if (env_v->value)
			ft_printf("declare -x %s=\"%s\"\n", env_v->key, env_v->value);
		else
			ft_printf("declare -x %s\n", env_v->key);
		env_v = env_v->next;
	}
	return (EXIT_SUCCESS);
}
