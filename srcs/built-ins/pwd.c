/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:23:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/18 18:54:15 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	directory[PATH_MAX];

	if (getcwd(directory, sizeof(directory)) != NULL)
		printf("%s\n", directory);
	else
	{
		perror("pwd error:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
