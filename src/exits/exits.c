#include "../includes/minishell.h"

void	exit_mini(t_mini *mini, int errnbr)
{
	if (mini)
	{
		free(mini);
	}
	exit(errnbr);
}