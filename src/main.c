/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/02/10 18:12:20 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <errno.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <termio.h> 
#include <signal.h> 
#include <readline/readline.h> 
#include <stdlib.h>
#include <stdbool.h>
//include "libft.h"
#include <sys/stat.h>

int main(int argc, char const **argv, char **envp)
{
	char *input;
	
	while (1)
	{
		input = readline("Minishell: ");
		printf("%s\n",input);
	}
	return 0;
}
