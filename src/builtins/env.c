/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/06 15:24:03 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(char **args)
{
	int i;

	i = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (EXIT_FAILURE);
}
