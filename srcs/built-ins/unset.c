/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:22:19 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 00:24:45 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

static t_env_v	*remove_head(t_env_v *head);

static t_env_v	*remove_env_var(t_env_v *head, char *key)
{
	t_env_v	*current;
	t_env_v	*prev;

	if (!head || !key)
		return (NULL);
	if (ft_strcmp(head->key, key) == 0)
		return (head = remove_head(head));
	prev = head;
	current = head->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return (head);
		}
		prev = current;
		current = current->next;
	}
	return (head);
}

static t_env_v	*remove_head(t_env_v *head)
{
	t_env_v	*temp;

	temp = head;
	head = head->next;
	free(temp->key);
	free(temp->value);
	free(temp);
	return (head);
}

void	ft_unset(t_shell *shell, char **argv)
{
	int		i;
	t_env_v	*aux;

	i = 0;
	while (argv[i])
	{
		aux = get_node_envp(shell->env_v, argv[i]);
		if (aux->value)
			remove_var_envp(shell, argv[i]);
		if (aux)
			shell->env_v = remove_env_var(shell->env_v, aux->key);
		i ++;
	}
}
