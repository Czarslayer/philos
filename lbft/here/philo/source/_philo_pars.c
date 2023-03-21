/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 02:13:46 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:44 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/_philo.h"

int	skoutcha(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' && str[i + 1])
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_if_all_inputs_valide(char *av[])
{
	int		i;
	long	check;

	i = 1;
	while (av[i])
	{
		if (!skoutcha(av[i]))
			return (0);
		check = ft_atoi(av[i]);
		if (check < 0 || check > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	full_philo_info(int ac, char *av[], t_philo_info *info)
{
	if (!check_if_all_inputs_valide(av) || ac < 5 || ac > 6)
		return (0);
	info->number_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->number_of_times_each_philo_eat = -1;
	if (av[5])
		info->number_of_times_each_philo_eat = ft_atoi(av[5]);
	return (1);
}
