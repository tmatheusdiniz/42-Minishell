/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:05 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/23 11:29:40 by alberto          ###   ########.fr       */
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

int	echo(char **input)
{
	int i;
	bool printline;

	i = 0;
	printline = true;
	while (str[1][i] && check_flag(str[1]))
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
