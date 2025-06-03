/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:06 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/03 17:08:47 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <minishell.h>

static void	user_output(t_shell *shell)
{
	char	*code;
	char	*cwd;
	char	*tmp;

	code = ft_itoa(exit_code(-1));
	cwd = getcwd(NULL, 0);
	if (!code || !cwd)
		return (free(code), free(cwd), malloc_failure(shell, "user_output"));
	tmp = ft_strjoin(PROMPT_START, code);
	free(code);
	if (!tmp)
		return (free(cwd), malloc_failure(shell, "user_output"));
	code = ft_strjoin(tmp, PROMPT_MID);
	free(tmp);
	if (!code)
		return (free(cwd), malloc_failure(shell, "user_output"));
	tmp = ft_strjoin(code, cwd);
	free(code);
	free(cwd);
	if (!tmp)
		return (malloc_failure(shell, "user_output"));
	shell->cwd = ft_strjoin(tmp, PROMPT_END);
	free(tmp);
	if (!shell->cwd)
		malloc_failure(shell, "user_output");
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
	shell->input_split = parsing(shell->input, shell);
	control(shell, envp);
}
