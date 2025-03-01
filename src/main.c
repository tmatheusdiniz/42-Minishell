/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/01 17:34:10 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	start_check(t_mini *mini, int ac, char **av)
{
	
}

bool	init_data(t_mini *mini, char **env)
{
	
}

int main(int argc, char const **argv, char **envp)
{
	t_mini mini;
	
	//int argc, char const **argv, char **envp
	ft_memset(&mini, 0, sizeof(t_mini));
	if (!start_check(&mini, argc, argv) || !init_data(&mini, env))
	{
		exit_mini(&mini, EXIT_FAILURE);
	}
		
}
