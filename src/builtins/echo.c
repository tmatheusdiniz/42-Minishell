/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:05 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/17 18:21:31 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool check_flag(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] == 'n')
		i++;
	if (str[i] == 0)
		return (true);
	else 
		return (false);
}

int	echo(char *str)
{
	int i;
	bool printline;

	i = 0;
	printline = true;
	while (str[i] && check_flag(str))
	{
		printline = false;
		i++;
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (printline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
