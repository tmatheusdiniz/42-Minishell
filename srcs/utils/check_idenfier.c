/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:04:32 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/02 13:04:42 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <minishell.h>

static int	get_var_name_len(const char *str);
static int	is_valid_first_char(char c);

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	is_valid_first_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	get_var_name_len(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

int	is_valid_export_identifier(const char *identifier)
{
	int	i;
	int	name_len;

	if (!identifier || !*identifier)
		return (0);
	if (identifier[0] == '-' || identifier[0] == '+')
		return (0);
	name_len = get_var_name_len(identifier);
	if (name_len == 0)
		return (0);
	if (!is_valid_first_char(identifier[0]))
		return (0);
	i = 1;
	while (i < name_len)
	{
		if (!is_valid_var_char(identifier[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_identifier(char *str)
{
	if (!is_valid_export_identifier(str))
	{
		print_export_error(str);
		exit_code(1);
		return (0);
	}
	return (1);
}
