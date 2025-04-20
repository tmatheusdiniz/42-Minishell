/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:24 by mreinald          #+#    #+#             */
/*   Updated: 2024/11/09 23:59:58 by mreinald         ###   ########.fr       */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:17:15 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 00:20:18 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*duplicate;

	str = (char *)ft_calloc(sizeof(char), (ft_strlen((char *)str) + 1));
	if (!str)
		return (NULL);
	i = 0;
	duplicate = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	while (str[i])
	{
		duplicate[i] = str[i];
		i ++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
