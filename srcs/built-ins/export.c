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
static void	only_one_var(t_mini *mini, char *argument);
static void	set_value(char **arguments);

static void	parse_of_arguments(t_mini *mini, char *argument)
{
	char	**split_re;

	if (!(ft_strchr(argument, '=')))
		only_one_var(mini, argument);
	else
	 	set_value(split_re);
	
}

// First i'm going to see if there is "=" in the second argument (key = value),
// e.g: export KEY="VALUE"
// if so, i'm going to put the value into the key and set it in the Env vars.
// if not, i'm just set the key in the Env vars, and value is setted as empty.


// This one is where i'm making the second way

static void	only_one_var(t_mini *mini, char *argument)
{
	int	i;

	i = 0;
	
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

void	export_func(t_mini *mini, char *argument)
{
	
	if (!argument)
		//print_all_var(mini);
	else
		//parse_of_arguments(mini->env_v, argument);
}
