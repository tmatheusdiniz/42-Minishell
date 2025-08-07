/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:22:29 by alberto           #+#    #+#             */
/*   Updated: 2025/08/07 17:11:04 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**prepare_argv_for_exec(char **argv)
{
	char	**clean_argv;
	int		i;
	int		count;
	int		len;

	i = 0;
	count = 0;
	while (argv[count])
		count++;
	clean_argv = ft_calloc(sizeof(char *), count + 1);
	if (!clean_argv)
		return (NULL);
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		if (len >= 2
			&& ((argv[i][0] == '\'' && argv[i][len - 1] == '\'')
				|| (argv[i][0] == '"' && argv[i][len - 1] == '"')))
			clean_argv[i] = ft_substr(argv[i], 1, len - 2);
		else
			clean_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	clean_argv[i] = NULL;
	return (clean_argv);
}
