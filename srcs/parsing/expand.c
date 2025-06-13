/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:07:45 by cda-fons          #+#    #+#             */
/*   Updated: 2025/06/13 17:55:33 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	in_quotes(char cur, bool flag, int quotes)
{
	if (cur == quotes && flag)
	{
		flag = false;
		return (flag);
	}
	if (cur == quotes)
		flag = true;
	return (flag);
}

char	*change_expansible(t_shell *mini, char *input, int *inc, char *string)
{
	char	*env_var;
	int		c;
	t_env_v	*node_env;

	node_env = NULL;
	env_var = check_env_var(input, inc);
	node_env = get_env_node_parsing(mini, env_var, node_env);
	if (node_env)
	{
		c = 0;
		while (node_env->value[c])
		{
			string[inc[1]] = node_env->value[c];
			inc[1]++;
			c++;
		}
		return (free(env_var), string);
	}
	else
		return (free(env_var), NULL);
}

char	*change_input(t_shell *mini, char *input, int *inc, bool no_expand)
{
	char	string[999];
	bool	d_flag;
	bool	s_flag;

	d_flag = false;
	s_flag = false;
	while (input[inc[0]])
	{
		s_flag = in_quotes(input[inc[0]], s_flag, '\'');
		d_flag = in_quotes(input[inc[0]], d_flag, '"');
		if (input[inc[0]] == '$' && ((d_flag && s_flag) || (!d_flag && !s_flag)
				|| (d_flag && !s_flag)) && !no_expand)
			change_expansible(mini, input, inc, string);
		else
		{
			string[inc[1]] = input[inc[0]];
			inc[1]++;
			inc[0]++;
		}
	}
	string[inc[1]] = '\0';
	return (ft_strdup(string));
}

char	*expand(char *input, t_shell *mini)
{
	char	*new_input;
	int		inc[2];
	bool	no_expand;

	inc[0] = 0;
	inc[1] = 0;
	
	no_expand = expand_check(input);
	if (!input || !mini)
		return (NULL);
	new_input = change_input(mini, input, inc, no_expand);
	if (!new_input)
		return (NULL);
	new_input = clean_quotes(new_input, 0, 0);
	return (new_input);
}
