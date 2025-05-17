/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:srcs/built-ins/env.c
/*   Created: 2025/03/06 15:24:02 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/06 20:25:19 by alberto          ###   ########.fr       */
=======
/*   Created: 2024/04/16 18:10:41 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/16 20:41:11 by cda-fons         ###   ########.fr       */
>>>>>>> Parsing:Lib/Libft/ft_substr.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_env_var(char **envp, char *new_var)
{
	int	i;

	i = 0;
<<<<<<< HEAD:srcs/built-ins/env.c
	while (envp[i])
		i ++;
	envp[i] = (char *)malloc(sizeof(char *) * ft_strlen(new_var));
	if (!envp[i])
		return (1);
	return (0);
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
=======
	size = (size_t)ft_strlen(s);
	if (len > size)
		len = size;
	if (size <= start || size == 0)
		len = 0;
	if (len > size - start)
		len = size - start;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (i < len)
>>>>>>> Parsing:Lib/Libft/ft_substr.c
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
