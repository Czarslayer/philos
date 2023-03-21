/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 02:10:34 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:38 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/_philo.h"

void	ft_print(char *str, t_philo *philo, char *color)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%s%lu : philo [%d] => %s \033[0m\n", color, get_time() \
	- philo->info.start_time, philo->philo_id + 1, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleep_and_think(t_philo *philo)
{
	ft_print("is sleeping ZzZzZz", philo, CYAN);
	ft_usleep(philo->info.time_to_sleep);
	ft_print("is thinking", philo, WHITE);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *act_philo)
{
	t_philo	*philo;

	philo = (t_philo *) act_philo;
	while (1)
	{
		if (philo->info.number_of_times_each_philo_eat != -1 && philo->maels >= \
		philo->info.number_of_times_each_philo_eat)
			continue ;
		pthread_mutex_lock(philo->right_fork);
		ft_print("take right fork Ψ", philo, WHITE);
		pthread_mutex_lock(philo->left_fork);
		ft_print("take left fork Ψ", philo, WHITE);
		pthread_mutex_lock(&philo->data->last_meal_check);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->data->last_meal_check);
		ft_print("is eating 🍝", philo, YELLOW);
		ft_usleep(philo->info.time_to_eat);
		pthread_mutex_lock(philo->data->meals);
		philo->maels++;
		pthread_mutex_unlock(philo->data->meals);
		put_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
