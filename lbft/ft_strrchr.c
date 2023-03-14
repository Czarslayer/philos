/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:31:13 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/29 18:52:07 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	if(!s)
		return(NULL);
	len = ft_strlen(s);
	while (len--)
	{
		if (s[len] == (char)c)
		{
			return ((char *)s + len);
		}
	}
	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	return (0);
}
