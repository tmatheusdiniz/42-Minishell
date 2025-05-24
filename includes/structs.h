/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:19:07 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/07 14:24:01 by mreinald         ###   ########.fr       */
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
	char	*cwd;
	char	**input_split;
	char	**envp;
	t_env_v	*env_v;
}		t_shell;

#endif
