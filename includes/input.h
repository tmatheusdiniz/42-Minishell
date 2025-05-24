/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:34:25 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/24 21:43:48 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <stdbool.h>

bool	input_validation(t_shell *shell)
{
	if (shell->input)
		return (true);
	return (false);
}
