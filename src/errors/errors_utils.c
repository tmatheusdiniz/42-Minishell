/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:23:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/18 01:02:14 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief 
/// @param mini 
/// @param message 
/// @param errnbr 
void	mini_errors(t_mini *mini, char *message, int errnbr)
{
	free(mini);
	error_message(message);	
	exit(errnbr);
}
/// @brief 
/// @param errnbr 
/// @param message 
void	error_message(char *message)
{
	ft_putendl_fd(message, 2);
}