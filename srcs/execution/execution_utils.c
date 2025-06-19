/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:00:31 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:01 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_whatis(void *root)
{
	int	*type_ptr;

	type_ptr = (int *)root;
	if (*type_ptr == EXEC)
		return (EXEC);
	else if (*type_ptr == PIPE)
		return (PIPE);
	else if (*type_ptr == INREDIR)
		return (INREDIR);
	else if (*type_ptr == OUTREDIR)
		return (OUTREDIR);
	return (-1);
}
