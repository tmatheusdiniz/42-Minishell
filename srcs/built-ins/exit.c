/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:49 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/29 22:41:52 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <minishell.h>

static void	exit_sucess(t_shell *shell, t_exec *exec_node);
static int	ft_is_numeric(char *str);
static void	not_is_numeric(t_shell *shell, char *str);

static int	check_limits(char *str, long long number)
{
	if (number > LLONG_MAX || number < LLONG_MIN)
		return (0);
	if (number == LLONG_MAX && ft_strcmp(str, "9223372036854775807"))
		return (0);
	if (number == LLONG_MIN && ft_strcmp(str, "-9223372036854775808"))
		return (0);
	return (1);
}

static int	ft_is_numeric(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = ft_atoll(str);
	if (!check_limits(str, number))
		return (0);
	while (str[i] == ' ')
		i ++;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i ++;
	}
	return (1);
}

static void	not_is_numeric(t_shell *shell, char *str)
{
	ft_putstr_fd("minishell : exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_shell_final(shell);
	//exit_code(2);
	exit(2);
}

static void	exit_sucess(t_shell *shell, t_exec *exec_node)
{
	long long	exit_cd;

	exit_cd = ft_atoll(exec_node->argv[1]);
	if (exec_node->argv[2])
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
	//	free_shell_final(shell);
		exit_code(1);
		return ;
	}
	free_shell_final(shell);
	exit ((unsigned char)exit_cd);
}

void	ft_exit(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node->argv[1])
	{
		free_shell_final(shell);
		exit(exit_code(-1));
	}
	if (ft_is_numeric(exec_node->argv[1]))
		exit_sucess(shell, exec_node);
	else
		not_is_numeric(shell, exec_node->argv[1]);
}
