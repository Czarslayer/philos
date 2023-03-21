/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:30:47 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:07 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_main.h"

void	philo_init(t_philo **philo, t_data **data)
{
	int				i;
	struct timeval	data_time;

	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eat");
	(*data)->forks = sem_open("forks", O_CREAT, 0644, \
	(*data)->info->num_of_philo);
	(*data)->print = sem_open("print", O_CREAT, 0644, 1);
	(*data)->eat = sem_open("eat", O_CREAT, 0644, 1);
	if ((*data)->forks == SEM_FAILED || (*data)->print == SEM_FAILED || \
	(*data)->eat == SEM_FAILED)
		exit_data("sem_open failed");
	(*data)->info->start_time = get_time();
	i = 0;
	while (i < (*data)->info->num_of_philo)
	{
		gettimeofday(&data_time, NULL);
		(*philo)[i].id = i;
		(*philo)[i].time_last_eat = data_time;
		(*philo)[i].eat_number = 0;
		(*philo)[i].data = *data;
		i++;
	}
}
