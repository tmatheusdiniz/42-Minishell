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

static void	exit_sucess(t_shell *shell, t_exec *exec_node, t_fork *frk);
static int	is_numeric(char *str);
static void	not_is_numeric(t_shell *shell, char *str, t_fork *frk);

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

static int	is_numeric(char *str)
{
	int			i;
	long long	number;

	i = 0;
	if (!str)
		return (0);
	number = ft_atoll(str);
	if (!check_limits(str, number))
		return (0);
	while (str[i] == ' ')
		i ++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i ++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i ++;
	}
	return (1);
}

static void	not_is_numeric(t_shell *shell, char *str, t_fork *frk)
{
	ft_putstr_fd("minishell : exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_fork_fds(frk);
	free_shell_final(shell);
	exit_code(2);
	exit(2);
}

static void	exit_sucess(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	long long	exit_cd;

	exit_cd = ft_atoll(exec_node->argv[1]);
	if (exec_node->argv[2])
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
		cleanup_fork_fds(frk);
		free_shell_final(shell);
		exit_code(1);
		exit (1);
	}
	print_exit();
	cleanup_fork_fds(frk);
	free_shell_final(shell);
	exit ((unsigned char)exit_cd);
}

void	ft_exit(t_shell *shell, t_exec *exec_node, t_fork *frk)
{
	if (!exec_node->argv[1])
		return ;
	if (is_numeric(exec_node->argv[1]))
		exit_sucess(shell, exec_node, frk);
	else
		not_is_numeric(shell, exec_node->argv[1], frk);
}
