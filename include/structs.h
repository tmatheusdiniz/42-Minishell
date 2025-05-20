/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:19:07 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/20 18:57:31 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env_v
{
	char			*key;
	char			*value;
	struct s_env_v	*next;
}	t_env_v;

typedef struct s_shell
{
	char	*input;
	char	**envp;
	void	*root;
	t_token	*tokens;
	t_env_v	*env_v;
}		t_shell;

#endif
