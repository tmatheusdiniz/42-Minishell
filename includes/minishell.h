#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> 
# include <stdio.h> 
# include <unistd.h> 
# include <sys/wait.h> 
# include <sys/types.h> 
# include <fcntl.h> 
# include <termio.h> 
# include <signal.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../Libft/libft.h"
# include <sys/stat.h>

# define NAME_SHELL "Minishell: "


typedef	struct	s_mini
{
	char	**args;
	char	**env;
}				t_mini;


//safe_utils.c
void safe_cd(char *chdir_arg, int flag);

//exits.c
void	exit_mini(t_mini *mini, int errnbr);

//			builtins
//cd
int	cd(char **args);
char *get_target(char **args);
int	change_dir(char *target);
void update_env(char *cwd);

//env
int	env(char **args);

//pwd
int	pwd(void);

#endif