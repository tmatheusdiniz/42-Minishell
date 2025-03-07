/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/06 15:24:25 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void update_env(char *cwd)
{
	char *oldpwd = getenv("PWD");
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", cwd, 1);
}

int	change_dir(char *target)
{
	char cwd[PATH_MAX];

	if (!target)
		return (ft_error("cd: HOME not set\n"));
	if (chdir(target) != 0)
		return (ft_error("cd"));
	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_error("getcwd"));
	update_env(cwd);
	return (0);

}

char *get_target(char **args)
{
	if (!args[1])
		return (getenv("HOME"));
	if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
		return(getenv("OLDPWD"));
	return (args[1]);
}

void	cd(t_mini *mini)
{
	char *target;

	char *target = getenv();
	if (!target)
		return (ft_error("cd: OLDPWD not set\n"));
	if (mini->args[1] && ft_strncmp(mini->args[1], "-", 2) == 0)
		printf("%s\n", target);
	change_dir(target);
}

/* int main(int argc, char *argv[])
{
	t_mini	*mini = (t_mini *)malloc(sizeof(t_mini));

	(void)argc;
	mini->args = argv;
    cd(mini);
    return 0;
} */