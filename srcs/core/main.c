/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:20 by cda-fons          #+#    #+#             */
/*   Updated: 2025/05/11 22:03:26 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 0);
	if (!shell)
		return (NULL);
	shell->envp = duplicate_env_v(envp);
	shell->env_v = NULL;
	shell->input = NULL;
	return (shell);
}

t_env_v	*init_env_v(t_env_v *env_v, char **envp)
{
	env_v = envp_to_linked_l(envp);
	if (!env_v)
		return (NULL);
	ft_sort_linked(env_v);
	return (env_v);
}

const char *redir_type_to_str(int type)
{
    if (type == INREDIR)
        return "<";
    else if (type == OUTREDIR)
        return ">";
    else if (type == APPEND)
        return ">>";
    return "?";
}
// ## PRINT ARVORE ##
// Imprime uma quantidade específica de espaços para indentação

void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
}

// Imprime a AST recursivamente
void print_ast_tree(void *node, int level)
{
    if (!node)
    {
        print_indent(level);
        printf("(NULL)\n");
        return;
    }
    
    // Verifica o tipo do nó
    int type = *((int *)node);
    
    if (type == EXEC)
    {
        t_exec *cmd = (t_exec *)node;
        print_indent(level);
        printf("COMMAND: ");
        
        if (!cmd->argv || !cmd->argv[0])
            printf("(empty)");
        else
        {
            int i = 0;
            while (cmd->argv[i])
            {
                printf("%s", cmd->argv[i]);
                if (cmd->argv[i + 1])
                    printf(" ");
                i++;
            }
        }
        printf("\n");
    }
    else if (type == PIPE)
    {
        t_pipe *pipe = (t_pipe *)node;
        print_indent(level);
        printf("PIPE\n");
        
        print_indent(level);
        printf("LEFT:\n");
        print_ast_tree(pipe->left, level + 1);
        
        print_indent(level);
        printf("RIGHT:\n");
        print_ast_tree(pipe->right, level + 1);
    }
    else if (type == OUTREDIR
		|| type == INREDIR
		|| type == APPEND)
    {
        t_redir *redir = (t_redir *)node;
        print_indent(level);
        printf("REDIR %s %s\n", 
               redir_type_to_str(redir->type), 
               redir->file ? redir->file : "(null)");
        
        print_indent(level);
        printf("NEXT:\n");
        print_ast_tree(redir->next, level + 1);
    }
    else
    {
        print_indent(level);
        printf("UNKNOWN NODE TYPE: %d\n", type);
    }
}
// ## PRINT LISTA TOKENS


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
	t_shell	*shell;
	char	**input_split;
	void	*root;

	if (argc > 1)
		return (ft_printf("Minishell: %s: No such file or directory", argv[1]));
	shell = init_shell(envp);
	shell->env_v = init_env_v(shell->env_v, shell->envp);
	input_split = NULL;
	while (1)
	{
		signal_init();
<<<<<<< HEAD
		shell->input = readline("Minishell: ");
		if (!shell->input)
			handle_errors(shell, "exit", SIGQUIT, input_split);
		if (!*shell->input)
			continue ;
		add_history(shell->input);
		input_split = ft_split(shell->input, ' ');
		input_split[0] = check_space(input_split[0]);
		if (check_command(shell, input_split) == -1)
			handle_errors(shell, "exit", SIGQUIT, input_split);
=======
		input = readline("Minishell: ");
		if (!input)
		{
			free_mini(mini, "exit", SIGQUIT, NULL);
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		input_split = parsing(input, mini);
		if (!input_split)
			continue ;
		create_token_list(input_split, mini, 0);
		print_token_list(mini->tokens);
		root = build_tree(mini->tokens);
		print_ast_tree(root, 0);
		cmds(input_split, mini);
>>>>>>> Parsing
	}
}
