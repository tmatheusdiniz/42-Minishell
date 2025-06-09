/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 03:03:53 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/09 18:46:25 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <stdbool.h>

//void	cmds(char **input_split, t_mini *mini);
char	**parsing(char *input, t_shell *mini);
bool	check_quotes(char *input_split, char quotes);
bool	in_quotes(char cur, bool flag, int quotes);

//tokenizer.c

void	create_token_list(char **input_split, t_shell *mini, int i);

//expand.c

char	*expand(char *input, t_shell *mini);

//tree.c

t_token	*search_redir(t_token *token);
t_token	*search_pipe(t_token *token);
void	*build_tree(t_token *tokens);
void	cut_tokens(t_token *tokens, t_token *base, t_token **left_tokens,
			t_token **right_tokens);
