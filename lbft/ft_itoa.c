/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:04:22 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/25 17:31:30 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digitcounter(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	store;
	int		i;
	char	*str;
	int		j;

	store = (long)n;
	i = digitcounter(store);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	if (store == 0)
		str[j++] = '0';
	if (store < 0)
	{
		str[j++] = '-';
		store = store * -1;
	}
	str[i--] = '\0';
	while (store != 0)
	{
		str[i--] = (store % 10) + '0';
		store = store / 10;
	}
	return (str);
}
