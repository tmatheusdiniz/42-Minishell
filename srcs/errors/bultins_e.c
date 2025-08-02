/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:15:55 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/02 13:17:07 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_export_error(char *identifier)
{
	if (identifier && (identifier[0] == '-' || identifier[0] == '+'))
	{
		if (identifier[1] == '=')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(identifier, 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("export: usage: export [-fn] [name[=value] ...] or export -p", 2);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(identifier, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(identifier, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
}
