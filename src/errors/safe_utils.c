#include "../../includes/minishell.h"

void safe_cd(char *chdir_arg, int flag)
{
	if (flag == 2)
	{
		fprintf(stderr,"Minishell: cd: too many arguments\n");
		return ;
	}
	else if (chdir(chdir_arg) == -1)
	{
		if (flag == 1)
			fprintf(2, "Minishel: cd: HOME not set\n");
		else
			fprintf(2, "Minishell: cd: %s: No such file or directory\n", chdir_arg);
		return ;
	}
}