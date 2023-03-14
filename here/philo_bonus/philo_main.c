/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 22:46:33 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:12 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_main.h"

void	*malak_lmout(void *arg)
{
	t_philo			*act_philo;
	struct timeval	x_time;

	act_philo = (t_philo *)arg;
	while (1)
	{
		gettimeofday(&x_time, NULL);
		_data_race_saver(x_time);
		if (_data_race_saver(x_time) - \
		_data_race_saver(act_philo->time_last_eat) >= \
		act_philo->data->info->time_to_die)
		{
			sem_wait(act_philo->data->print);
			printf("%ld %d %s \n", get_time() - \
			act_philo->data->info->start_time, act_philo->id + 1, "died");
			exit(1);
		}
	}
}

void	think_and_sleep(t_philo *act_philo)
{
	sem_post(act_philo->data->forks);
	sem_post(act_philo->data->forks);
	print_status(act_philo, "is sleeping");
	ft_usleep(act_philo->data->info->time_to_sleep);
	print_status(act_philo, "is thinking");
}

void	philo_routine(t_philo *act_philo)
{
	struct timeval	x_time;

	pthread_create(&act_philo->thread, NULL, &malak_lmout, act_philo);
	while (1)
	{
		sem_wait(act_philo->data->forks);
		print_status(act_philo, "take first fork");
		sem_wait(act_philo->data->forks);
		print_status(act_philo, "take second fork");
		gettimeofday(&x_time, NULL);
		act_philo->time_last_eat = x_time;
		print_status(act_philo, "is eating");
		ft_usleep(act_philo->data->info->time_to_eat);
		act_philo->eat_number++;
		if (act_philo->eat_number == \
		act_philo->data->info->num_of_times_each_philo_must_eat)
		{
			sem_post(act_philo->data->forks);
			sem_post(act_philo->data->forks);
			break ;
		}
		think_and_sleep(act_philo);
	}
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	t_philo			*philos;
	t_data			*data;
	t_norm			norm;

	full_info(argc, argv, &info);
	philos = (t_philo *) malloc (sizeof(t_philo) * info.num_of_philo);
	data = (t_data *) malloc (sizeof(t_data));
	norm.pids = (int *) malloc(sizeof(int) * (info.num_of_philo + 1));
	if (!philos || !data || !norm.pids)
		exit_data("malloc failed");
	data->info = &info;
	philo_init(&philos, &data);
	norm.i = 0;
	while (norm.i < info.num_of_philo)
	{
		norm.pid = fork();
		if (norm.pid == 0)
			philo_routine(&philos[norm.i]);
		else
			norm.pids[norm.i] = norm.pid;
		norm.i++;
	}
	while (waitpid(-1, &norm.status, 0) > 0)
		killing_system(philos, &norm);
}
