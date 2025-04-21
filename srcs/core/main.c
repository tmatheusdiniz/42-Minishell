/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/21 20:35:18 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_mini	*init_mini(char **envp)
{
	t_mini	*mini;

	mini = ft_calloc(sizeof(t_mini), 1);
	if (!mini)
		mini_errors(mini, "Calloc: Calloc failed", 0);
	mini->env = duplicate_env(envp);
	return (mini);
}

void print_token_list(t_token *tokens)
{
    t_token *current;
    int count;

    if (!tokens)
    {
        printf("Token list is empty\n");
        return;
    }
    current = tokens;
    count = 0;
    printf("=== TOKEN LIST ===\n");
    while (current)
    {
        printf("Token %d:\n", count);
        printf("  Content: \"%s\"\n", current->token ? current->token : "NULL");
        printf("  Type: %d\n", current->type);
        printf("  Index: %d\n", current->index);
        printf("  Address: %p\n", (void *)current);
        printf("  Next: %p\n", (void *)current->next);
        printf("  Prev: %p\n", (void *)current->prev);
        printf("---------------\n");
        current = current->next;
        count++;
    }
    printf("Total tokens: %d\n", count);
    printf("=================\n");
}

int	main(int argc, char const **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	char	**input_split;

	(void)argv;
	(void)argc;
	mini = init_mini(envp);
	input = NULL;
	while (1)
	{
		signal_init();
		input = readline("Minishell: ");
		if (!input)
		{
			free_mini(mini, "exit", SIGQUIT, NULL);
			break ;
		}
		if (!*input)
			continue;
		add_history(input);
		input_split = parsing(input);
		create_token_list(input_split, mini);
		print_token_list(mini->tokens);
		cmds(input_split, mini);
	}
}
