/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:12:41 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:21 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_main.h"

void	exit_data(char *str)
{
	printf("Error: %s \n", str);
	exit(1);
}

void	skoutcha(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' && str[i + 1])
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			exit_data("invalid data input");
		i++;
	}
}

void	check_if_all_inputs_valide(char *av[])
{
	int		i;
	long	check;

	i = 1;
	while (av[i])
	{
		skoutcha(av[i]);
		check = ft_atoi(av[i]);
		if (check < 0 || check > INT_MAX)
			exit_data("invalid data input");
		i++;
	}
}

void	full_info(int ac, char *av[], t_philo_info *info)
{
	check_if_all_inputs_valide(av);
	if (ac < 5 || ac > 6)
		exit_data("invalid number of arguments");
	info->num_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->num_of_times_each_philo_must_eat = -1;
	if (av[5])
		info->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
}
