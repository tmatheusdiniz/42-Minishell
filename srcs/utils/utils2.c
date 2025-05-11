/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:57:45 by alberto           #+#    #+#             */
/*   Updated: 2025/05/10 23:46:40 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clean_quotes(char *var)
{
	int		i;
	char	new_var[999];
	int		j;

	i = 0;
	j= 0;
	while (var[i])
	{
		if (ft_isalpha(var[i]))
		{
			new_var[j] = var[i];
			i++;
			j++;
		}
		else
			i++;
	}
	new_var[j] = '\0';
	free(var);
	return(ft_strdup(new_var));
}
