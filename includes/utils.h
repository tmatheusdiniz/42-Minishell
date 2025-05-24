/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:56:50 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/08 13:58:04 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <structs.h>

// ----------Main----------
int		check_args(int argc, char const **argv, char **envp);
int		check_command(t_shell *shell, char **input);
void	handle_env_vars(t_shell *shell, char **envp);
t_shell	*init_shell(void);

// ----------Linked List----------
int		get_index_env(t_env_v *env_v, char *var);
int		count_linked_list(t_env_v *list);
t_env_v	*envp_to_linked_l(char **envp);
t_env_v	*get_node_envp(t_env_v *env_v, char *KEY);

// ----------Print----------
void	print_exit(void);

// free
void	free_shell(t_shell *shell);
void	clean_matrix(char **matrix);

// ----------General----------
int		ft_strcmp(char *s1, char *s2);
char	*check_space(char *input);
char	**duplicate_env_v(char **envp);

#endif
