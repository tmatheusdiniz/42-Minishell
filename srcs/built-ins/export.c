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

static void	print_all_var(t_env_v *env_v);
static void	only_one_var(t_env_v *env_v, char *argument);
//static void	set_value(char **arguments);

static void	parse_of_arguments(t_env_v *env_v, char *argument)
{
	//char	**split_re;
//
	if (!(ft_strchr(argument, '=')))
		only_one_var(env_v, argument);
	//else
	// 	set_value(split_re);
}

// First i'm going to see if there is "=" in the second argument (key = value),
// e.g: export KEY="VALUE"
// if so, i'm going to put the value into the key and set it in the Env vars.
// if not, i'm just set the key in the Env vars, and value is setted as empty.


// This one is where i'm making the second way

static void	only_one_var(t_env_v *env_v, char *argument)
{
	set_only_key(argument, env_v);
}

/*
static void	set_value(char **arguments)
{
	// Here doing the first way
}
*/

static void	print_all_var(t_env_v *env_v)
{
	while (env_v)
	{
		if (env_v->VALUE)
			ft_printf("declare -x %s=\"%s\"\n", env_v->KEY, env_v->VALUE);
		else
			ft_printf("declare -x %s\n", env_v->KEY);
		env_v = env_v->next;
	}
}

void	export_func(t_mini *mini, char *argument)
{
	if (!mini->env_v)
	{
		mini->env_v = envp_to_l_l(mini->env);
		ft_sort_linked(mini->env_v, 0);
	}
	if (!argument)
		print_all_var(mini->env_v);
	else
		parse_of_arguments(mini->env_v, argument);
}
