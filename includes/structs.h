/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:19:07 by mreinald          #+#    #+#             */
/*   Updated: 2025/05/21 14:44:52 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token	t_token;
typedef struct s_exec	t_exec;
typedef struct s_redir	t_redir;
typedef struct s_pipe	t_pipe;
typedef struct s_env_v	t_env_v;

typedef struct s_exec
{
	int		type;
	char	**argv;
}				t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	void	*next;
}				t_redir;

typedef struct s_pipe
{
	int		type;
	void	*left;
	void	*right;
}				t_pipe;

typedef struct s_env_v
{
	char			*key;
	char			*value;
	struct s_env_v	*next;
}	t_env_v;

typedef struct s_token
{
	char	*token;
	int		type;
	int		index;
	t_token	*next;
	t_token	*prev;
}				t_token;

typedef struct s_shell
{
	char	*input;
	char	*cwd;
	char	**input_split;
	char	**envp;
	void	*root;
	t_token	*tokens;
	t_env_v	*env_v;
}		t_shell;

#endif
