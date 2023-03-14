/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:23:58 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/29 18:34:43 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	 if (ft_memcmp(dst, src, len) == 0)
	 	return (dst);
	if ((src < dst)
		&& ((size_t)src + len > (size_t)dst))
	{
		while (len--)
		{
			((char *)dst)[len] = ((char *)src)[len];
		}
		return (dst);
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
