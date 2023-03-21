/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 02:12:57 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:41 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/_philo.h"

int	init_data_mutex(t_data **data, t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_mutex_init(&(*data)->forks[i], NULL) == -1)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(*data)->meals[0], NULL) == -1)
		return (0);
	if (pthread_mutex_init(&(*data)->print, NULL) == -1)
		return (0);
	if (pthread_mutex_init(&(*data)->last_meal_check, NULL) == -1)
		return (0);
	return (1);
}

int	run_data_philo(t_philo **philo, t_data **data, t_philo_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->number_of_philo)
	{
		(*philo)[i].philo_id = i;
		(*philo)[i].data = *data;
		(*philo)[i].right_fork = &(*data)->forks[i];
		(*philo)[i].left_fork = &(*data)->forks[(i + 1) \
			% info->number_of_philo];
		(*philo)[i].info = *info;
		(*philo)[i].maels = 0;
		(*philo)[i].last_meal = get_time();
		if (pthread_create(&(*philo)[i].thread, NULL, \
			&routine, &(*philo)[i]) == -1)
			return (0);
		usleep(50);
		i++;
	}
	return (1);
}
