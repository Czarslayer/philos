/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:43:31 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/23 15:32:06 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len2 = ft_strlen(s2);
	len1 = ft_strlen(s1);
	i = 0;
	j = 0;
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr != NULL)
	{
		while (s1[i] != '\0')
			ptr[j++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			ptr[j++] = s2[i++];
		ptr[j] = '\0';
	}
	return (ptr);
}
