/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:07:19 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/07 14:18:55 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <structs.h>

// ----------cd----------
void	ft_cd(t_env_v *env_v, char **input);
void	update_pwd(t_env_v *env_v);
void	update_oldpwd(t_env_v *env_v);
int		change_dir(t_env_v *env_v, char *target);
char	*get_target(t_env_v *env_v, char *input);

// ----------export----------
void	ft_export(t_env_v *env_v, char *argument);
void	ft_sort_linked(t_env_v *env_v);
void	*create_node(char *key_name, char *content);
char	**aux_set(char *envp);
t_env_v	*set_only_key(t_env_v *env_v, char *key);

// ----------env----------
int		ft_env(char **envp);
int		add_env_var(char **envp, char *new_var);

// ----------pwd----------
int		ft_pwd(void);

// ----------echo----------
int		ft_echo(char **input);

// ----------unset----------
int		ft_unset(t_env_v *env_v, char *env_var);

#endif
