/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:01:48 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/19 16:25:18 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_all_var(char **envp);
static void	only_one_var(char **envp, char *argument);
static void	set_value(char **arguments);

extern char **environ;

static void	parse_of_arguments(char **envp, char *argument)
{
	char	**split_re;

	// Modify the parse
	split_re = ft_split(argument, ' ');
	if (!split_re)
		return ; // Handle error
	if (!(split_re[1]))
		only_one_var(envp, split_re[0]);
	else
	 	set_value(split_re);
}

// First i'm going to see if there is "=" in the second argument (key = value),
// e.g: export KEY="VALUE"
// if so, i'm going to put the value into the key and set it in the Env vars.
// if not, i'm just set the key in the Env vars, and value is setted as empty.

static void	only_one_var(char **envp, char *argument)
{
	int	i;

	i = 0;
	char	*save;
	// This one is where i'm making the second way
	while (envp[i])
		i++;
	save = ft_strjoin(argument, "=");
	envp[i] = ft_strdup(argument);
}

static void	set_value(char **arguments)
{
	// Here on the first way
}

static void	print_all_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i ++;
	}
}

void	export_func(char **envp, char *argument)
{
	if (!argument)
		print_all_var(envp);
	else
		parse_of_arguments(envp, argument);
}
