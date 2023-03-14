/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:49:50 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/23 16:36:46 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*stcr(char *s1, char *set)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			return (s1 + i);
		j = 0;
		i++;
	}
	return (s1 + i);
}

static char	*edcr(char *s1, char *set)
{
	size_t	i;
	int		j;
	int		k;

	k = 0;
	j = 0;
	i = ft_strlen(s1);
	while (i > 0)
	{
		while (set[j] != '\0' )
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			return (s1 + i + 1);
		j = 0;
		i--;
	}
	return (s1 + i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	len;
	char	*ptr2;
	char	*ptr1;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	ptr1 = stcr((char *)s1, (char *)set);
	if (ptr1[0] == '\0')
		ptr2 = (char *) s1 + len;
	else
		ptr2 = edcr((char *)s1, (char *)set);
	while (ptr2 != ptr1)
	{
		ptr2 -= 1;
		i++;
	}
	ptr1 = ft_substr(ptr1, 0, i);
	return (ptr1);
}
