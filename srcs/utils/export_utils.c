/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:34 by mreinald          #+#    #+#             */
/*   Updated: 2025/04/26 21:27:30 by mreinald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free (matrix);
}

/*
void	ft_sort_params(char **arg, int argc)
{
	int		i;
	int		j;
	char	*save;

	i = 1;
	j = 1;
	while (j < argc)
	{
		i = 1;
		while (i < argc)
		{
			if (arg[i + 1] && ft_strcmp(arg[i], arg[i + 1]) > 0)
			{
				save = arg[i];
				arg[i] = arg[i + 1];
				arg[i + 1] = save;
			}
			i ++;
		}
		j ++;
	}
}
*/

void	*create_node(char *key_name, char *content)
{
	t_env_v	*env_v;

	if (!key_name)
		return (NULL);
	env_v = (t_env_v *)malloc(sizeof(t_env_v));
	if (!env_v)
		return (NULL);
	env_v->KEY = ft_strdup(key_name);
	if (!env_v->KEY)
		return (free(env_v), NULL);
	if (!content)
		env_v->VALUE = NULL;
	else
		env_v->VALUE = ft_strdup(content);
	env_v->next = NULL;
	return (env_v);
}

void	*envp_to_l_l(char **envp)
{
	int		i;
	t_env_v	*head;
	t_env_v	*current;
	t_env_v	*new_node;
	char	**save;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		save = ft_split(envp[i++], '=');
		if (!save)
			return (NULL);
		new_node = create_node(save[0], save[1]);
		clean_matrix(save);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
	}
	return ((t_env_v *)head);
}
