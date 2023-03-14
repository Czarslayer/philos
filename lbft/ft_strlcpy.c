/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:28:19 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/29 18:42:54 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lsize;

	lsize = 0;
	if(!dst || !src)
		return(0);
	while (src[lsize] != '\0')
	{
		lsize++;
	}
	if (dstsize == 0)
		return (lsize);
	i = 0;
	while (src[i] != '\0' && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lsize);
}
