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

#include "../../include/minishell.h"

static void	remove_head(t_env_v *head);

static int	remove_env_var(t_env_v *head, char *key)
{
	t_env_v	*current;
	t_env_v	*prev;

	if (!head || !key)
		return (-1);
	if (ft_strcmp(head->key, key) == 0)
		return (remove_head(head), 0);
	prev = head;
	current = head->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

static void	remove_head(t_env_v *head)
{
	t_env_v	*temp;

	temp = head;
	head = head->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}

int	ft_unset(t_env_v *env_v, char *env_var)
{
	if (!env_v)
		return (-1);
	if (remove_env_var(env_v, env_var))
		return (-1);
	return (0);
}
