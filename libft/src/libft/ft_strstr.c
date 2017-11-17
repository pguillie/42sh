/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:30:32 by pguillie          #+#    #+#             */
/*   Updated: 2017/10/27 23:48:42 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		if (!(ft_strncmp(haystack + i, needle, ft_strlen(needle))))
			return ((char*)haystack + i);
		i++;
	}
	return (NULL);
}
