/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:srcs/built-ins/pwd.c
/*   Created: 2025/03/06 15:23:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/01 16:19:38 by cda-fons         ###   ########.fr       */
=======
/*   Created: 2025/04/10 14:49:54 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/16 17:42:31 by cda-fons         ###   ########.fr       */
>>>>>>> Parsing:Lib/Libft/ft_free_split.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD:srcs/built-ins/pwd.c
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
=======
void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
>>>>>>> Parsing:Lib/Libft/ft_free_split.c
}
