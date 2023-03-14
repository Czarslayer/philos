/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:20:20 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/29 18:35:21 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{	
	size_t	i;

	if(!b)
		return(NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
			i++;
	}
	return (b);
}
