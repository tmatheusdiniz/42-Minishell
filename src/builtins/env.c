#include "../../includes/minishell.h"

int	env(char **args)
{
	int i;

	i = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (EXIT_FAILURE);
}
