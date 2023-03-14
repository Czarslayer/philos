/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:13:27 by mabahani          #+#    #+#             */
/*   Updated: 2022/10/23 17:05:32 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strcounter(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				i++;
		counter++;
		}
		else
			i++;
	}
	return (counter);
}

static char	*mini_allocator(char **ptr, char *str, char c)
{
	int	i;
	int	j;
	int	k;
	int	save;

	i = 0;
	while (str[i] == c)
		i++;
	save = i;
	k = 0;
	j = 0;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		k++;
	}
	*ptr = malloc ((k + 1) * sizeof (char));
	if (!*ptr)
		return (0);
	while (str[save] != c && str[save] != '\0')
		(*ptr)[j++] = str[save++];
	(*ptr)[j] = '\0';
	return (str + save);
}

static void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
}

char	**ft_split(char *str, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		wc;

	j = 0;
	i = 0;
	if (str == NULL)
		return (ptr = NULL);
	wc = strcounter(str, c);
	ptr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (ptr != NULL)
	{
		while (i < wc)
		{
			str = mini_allocator(ptr + i, str, c);
			if (str == NULL)
				free_double_ptr (ptr);
			i++;
		}
		ptr[wc] = NULL;
	}
	return (ptr);
}
