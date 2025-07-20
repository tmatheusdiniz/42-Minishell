/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:19:07 by mreinald          #+#    #+#             */
/*   Updated: 2025/07/21 00:32:30 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <libft.h>

typedef struct s_token	t_token;
typedef struct s_exec	t_exec;
typedef struct s_redir	t_redir;
typedef struct s_pipe	t_pipe;
typedef struct s_env_v	t_env_v;

typedef struct s_exec
{
	int		type;
	char	*cmd_path;
	char	**argv;
	t_list	*infile;
	t_list	*outfile;
}			t_exec;

typedef struct s_outredir
{
	int		type;
	char	*file;
	void	*next;
}				t_outredir;

typedef struct s_inredir
{
	int		type;
	char	*file;
	void	*next;
}				t_inredir;

typedef struct s_append
{
	int		type;
	char	*file;
	void	*next;
}				t_append;

typedef struct s_heredoc
{
	int		type;
	char	*delimiter;
	char	*content;
	void	*next;
}				t_heredoc;

typedef struct s_pipe
{
	int		type;
	void	*left;
	void	*right;
}				t_pipe;

typedef struct s_token
{
	char	*token;
	int		type;
	int		index;
	t_token	*next;
	t_token	*prev;
}				t_token;

typedef struct s_env_v
{
	char			*key;
	char			*value;
	t_env_v			*next;
}				t_env_v;

typedef struct s_tokens
{
	t_token	**tokens;
	int		count;
}	t_tokens;

typedef struct s_fork
{
	int		fd_in;
	int		fd_out;
	int		nbr_cmds;
	int		**pipe;
	pid_t	*pid;
}				t_fork;

typedef struct s_shell
{
	char	*input;
	char	*cwd;
	char	**envp;
	void	*root;
	void	*original_root;
	t_token	*tokens;
	t_env_v	*env_v;
}				t_shell;

#endif
