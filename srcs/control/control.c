/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:06 by mreinald          #+#    #+#             */
/*   Updated: 2025/08/08 16:57:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	handle_input(t_shell *shell)
{
	if (shell->input && shell->input[0] != '\0')
		add_history(shell->input);
	if (shell->input && input_validation(shell))
	{
		free_shell_part(shell);
		return (1);
	}
	if (!shell->input || !ft_strcmp(shell->input, "exit"))
	{
		print_exit();
		return (2);
	}
	return (0);
}

static void	process_command(t_shell *shell)
{
	if (parsing(shell) == 0)
		ft_execution(shell);
	else
		cleanup_parsing_error(shell);
	if (shell->original_root != NULL)
		free_shell_part(shell);
}

void	control(t_shell *shell, char **envp)
{
	int	status;

	signal_handler();
	user_output(shell);
	shell->input = readline(shell->cwd);
	free(shell->cwd);
	shell->cwd = NULL;
	status = handle_input(shell);
	if (status == 1)
		control(shell, envp);
	else if (status == 2)
		return ;
	else
	{
		process_command(shell);
		control(shell, envp);
	}
}
