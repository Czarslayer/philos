/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:31:37 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/29 18:41:41 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if(!dst || !src)
		return(0);
	dstlen = 0;
	srclen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (dstsize == 0 && !dst)
		return (srclen);
	while (dst[dstlen] != '\0')
		dstlen++;
	if (dstsize <= dstlen || dstsize == 0)
		return (srclen + dstsize);
	while (i < dstsize - dstlen - 1 && src[i] != '\0')
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

int main()
{
    char src[] = "hello";
    printf("%zu",ft_strlcat(NULL,src,5));
}
