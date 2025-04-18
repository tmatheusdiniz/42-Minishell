/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:lib/Libft/srcs/ft_strdup.c
/*   By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:24 by mreinald          #+#    #+#             */
/*   Updated: 2024/11/09 23:59:58 by mreinald         ###   ########.fr       */
=======
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:17:15 by cda-fons          #+#    #+#             */
/*   Updated: 2025/04/10 00:20:18 by alberto          ###   ########.fr       */
>>>>>>> 08127014cf98e6532efbcb8d8a966a35efa88dc0:Lib/Libft/ft_strdup.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*duplicate;

<<<<<<< HEAD:lib/Libft/srcs/ft_strdup.c
=======
	str = (char *)ft_calloc(sizeof(char), (ft_strlen((char *)s) + 1));
	if (!str)
		return (NULL);
>>>>>>> 08127014cf98e6532efbcb8d8a966a35efa88dc0:Lib/Libft/ft_strdup.c
	i = 0;
	duplicate = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	while (s[i])
	{
		duplicate[i] = s[i];
		i ++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
