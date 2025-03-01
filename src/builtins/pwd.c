#include "../../includes/minishell.h"

int	pwd(void)
{
	char directory[PATH_MAX];

	if (getcwd(directory, sizeof(directory)) != NULL)
		printf("%s\n", directory);
	else
	{
		perror("pwd error:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
