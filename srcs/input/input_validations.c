/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:54 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/07 01:27:30 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

bool	input_validation(t_shell *shell)
{
	if (!shell->input[0])
		return (true);
	if (!*shell->input)
		return (exit_code(2));
	if (shell->input)
		shell->input = ft_strtrim(shell->input, "\t ");
	if (check_quotes(shell->input, '"')
		|| check_quotes(shell->input, '\''))
	{
		print_error(NAME_SHELL,
			" syntax error - the quote is open", NULL, NULL);
		return (exit_code(2));
	}
	return (false);
}
