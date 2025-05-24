/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:06 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/21 14:45:06 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "utils.h"
#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

static void	user_output(t_shell *shell)
{
	char	*prompt;
	char	*cwd;
	char	*code;
	char	*tmp;
	char	*tmp2;

	code = ft_itoa(exit_code(-1));
	cwd = getcwd(NULL, 0);
	prompt = ESC_START SHELL_NAME ESC_RESET;
	tmp = ft_strjoin(prompt, code);
	free (code);
	if (!tmp)
		malloc_failure(shell, "user_output");
	tmp2 = ft_strjoin(tmp, ESC_CODE);
	free (tmp);
	if (!tmp2)
		malloc_failure(shell, "user_output");
	tmp = ft_strjoin(tmp2, cwd);
	free (cwd);
	if (!tmp)
		malloc_failure(shell, "user_output");
	shell->cwd = ft_strjoin(tmp, SYMBOL);
	free (cwd);
	free (tmp);
}

void	control(t_shell *shell, char **envp)
{
	(void)envp;
	signal_handler();
	user_output(shell);
	shell->input = readline(shell->cwd);
	if (shell->input && input_validation(shell))
		add_history(shell->input);
	if (!shell->input || !ft_strcmp(shell->input, "exit"))
	{
		print_exit();
		free_shell(shell);
		return ;
	}
	control(shell, envp);
}
