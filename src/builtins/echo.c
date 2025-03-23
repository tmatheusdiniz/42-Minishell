/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:05 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/23 13:34:35 by cda-fons         ###   ########.fr       */
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
	int k;
	bool printline;

	k = 0;
	i = 1;
	printline = true;
	while (input[i] && check_flag(input[i]))
	{
		printline = false;
		i++;
	}
	while (input[i])
	{
		k = 0;
		while(input[i][k])
		{
			write(1, &input[i][k], 1);
			k++;
		}
		if (input[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (printline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
