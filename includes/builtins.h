/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:07:19 by mreinald          #+#    #+#             */
/*   Updated: 2025/06/03 15:32:59 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <structs.h>

// ----------cd----------

void	ft_cd(t_shell *shell, t_exec *exec_node);
void	change_dir(t_shell *shell, char *target);
int		update_pwd(t_env_v *env_v);
int		update_oldpwd(t_env_v *env_v);
char	*get_target(t_env_v *env_v, char *input);

// ----------export----------

void	ft_export(t_shell *shell);
void	ft_sort_linked(t_env_v *env_v);
void	*create_node(char *key_name, char *content);
int		modify_value_env(t_env_v *env_v, char *argument);
int		find_position(t_env_v *env_v, char *new_key, int linked_size);
int		check_duplicated(t_env_v *current, char *key);
char	**aux_set(char *envp);
t_env_v	*set_only_key(t_env_v *env_v, char *key);

// ----------env----------

void	ft_env(char **envp, char **arguments);
int		add_var_envp(char **envp, char *new_var);
int		remove_var_envp(char **envp, char *key);

// ----------pwd----------

void	ft_pwd(void);

// ----------echo----------

void	ft_echo(char **arguments);

// ----------unset----------

void	ft_unset(t_shell *shell);

// ----------exit----------

void	ft_exit(t_shell *shell);

#endif
