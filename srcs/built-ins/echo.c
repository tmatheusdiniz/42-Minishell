/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:05 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/01 16:14:14 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_flag(char *str)
{
	int	i;

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

void	ft_echo(char **arguments)
{
	int		i;
	bool	printline;

	i = 1;
	printline = true;
	while (arguments[i] && check_flag(arguments[i]))
	{
		printline = false;
		i++;
	}
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], 1);
		if (arguments[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (printline)
		write(1, "\n", 1);
}
