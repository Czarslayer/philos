/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:49:00 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:55 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/_philo.h"

int	meals_check(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philo->info.number_of_philo)
	{
		pthread_mutex_lock(philo->data->meals);
		if (philo[i].maels >= philo->info.number_of_times_each_philo_eat)
			count++;
		pthread_mutex_unlock(philo->data->meals);
		i++;
	}
	if (count == philo->info.number_of_philo)
		return (0);
	return (1);
}

int	the_god_of_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info.number_of_philo)
	{
		pthread_mutex_lock(&philo->data->last_meal_check);
		if (get_time() - philo[i].last_meal >= philo->info.time_to_die)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%s%lu : philo [%d] => %s \033[0m\n", RED, get_time() \
			- philo->info.start_time, philo->philo_id + 1, "is died [RIP] T-T");
			return (0);
		}
		pthread_mutex_unlock(&philo->data->last_meal_check);
		i++;
	}
	if (philo->info.number_of_times_each_philo_eat == -1)
		return (1);
	if (!meals_check(philo))
		return (0);
	return (1);
}

void	destroy_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info.number_of_philo)
		pthread_detach(philo[i++].thread);
	i = 0;
	while (i < philo->info.number_of_philo)
		pthread_mutex_destroy(&philo->data->forks[i++]);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	t_philo			*philos;
	t_data			*data;

	memset(&info, 0, sizeof(t_philo_info));
	if (!full_philo_info(argc, argv, &info) || info.number_of_philo == 0)
		return (printf("Error with yout inputs\n"), 0);
	philos = (t_philo *) malloc (sizeof(t_philo) * info.number_of_philo);
	data = (t_data *) malloc (sizeof(t_data));
	if (!philos || !data)
		return (0);
	data->forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) \
	* info.number_of_philo);
	data->meals = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	if (!init_data_mutex(&data, &info) || \
	!run_data_philo(&philos, &data, &info))
		return (0);
	while (1)
		if (!the_god_of_death(philos))
			break ;
	return (destroy_threads(philos), 0);
}
