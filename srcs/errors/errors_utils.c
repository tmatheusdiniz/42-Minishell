/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:23:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/08 19:05:46 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// temporary, after add other many more things for handle errors

void	error_message(char *message, int errnbr)
{
	errnbr = 2;
	ft_putendl_fd(message, errnbr);
}

<<<<<<< HEAD
void	handle_errors(t_shell *shell, char *message,
		int errnbr, char **inp_split)
{
	if (inp_split)
		free (inp_split);
	free_structs(shell);
	error_message(message, errnbr);
	exit(errnbr);
=======
int	print_error(char *str1, char *str2, char *str3, char *message)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
	{
		if (str1 || str2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(str3, 2);
		ft_putstr_fd("'", 2);
	}
	if (message)
	{
		if (str1 || str2 || str3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return (-1);
>>>>>>> Parsing
}
