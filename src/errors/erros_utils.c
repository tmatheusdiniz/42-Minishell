#include "../includes/minishell.h"

/// @brief 
/// @param mini 
/// @param message 
/// @param errnbr 
void	mini_errors(t_mini *mini, char *message, int errnbr)
{
	error_message(errnbr, message);	
	exit(errnbr);
}
/// @brief 
/// @param errnbr 
/// @param message 
void	error_message(int errnbr, char *message)
{
	ft_putendl_fd(message, 2);
}