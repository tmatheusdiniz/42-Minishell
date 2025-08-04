/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:53:24 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/20 18:42:58 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>

// ----------Free Final----------
void	free_shell_final(t_shell *shell);
void	free_env_v(t_env_v *env_v);

// ----------Free Frame----------
void	free_shell_part(t_shell *shell);
void	free_tokens(t_token **tokens);
void	free_tree(void *root);
void	cleanup_fork(t_fork *frk);
void	free_redir(void *root);
void	free_exec(void *root);

// ----------Free Redir----------
void	free_outredir(void *root);
void	free_inredir(void *root);
void	free_append(void *root);
void	free_heredoc(void *root);

// ----------Utils Free----------
void	clean_matrix(char **matrix);
void	cleanup_parsing_error(t_shell *shell);
void	cleanup_execution_error(t_shell *shell, t_fork *frk);
