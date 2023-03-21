/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <mabahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:21:42 by mabahani          #+#    #+#             */
/*   Updated: 2023/03/17 19:54:19 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

int arg_checker_zero(int number_philo, int time_to_die, int time_to_eat, int time_to_sleep)
{
	if (number_philo <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
		return (1);
	return (0);
}

int	data_checker(char **argv)
{
	int i;
	int j;

	i = 1;
	if(!argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if(argv[i][0] == '+')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int data_init(t_default **def, char **argv)
{
	if(data_checker(argv) == 1)
		return (1);
	(*def)->number_philo = atoi(argv[1]);
	(*def)->time_to_die = atoi(argv[2]);
	(*def)->time_to_eat = atoi(argv[3]);
	(*def)->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		(*def)->max_of_meals = atoi(argv[5]);
	else
		(*def)->max_of_meals = -1;
	if(arg_checker_zero((*def)->number_philo, (*def)->time_to_die, (*def)->time_to_eat, (*def)->time_to_sleep) == 1)
		return (1);
	return (0);
}



long gettimeofdays(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	printer(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutixes->print);
	printf("%lu %d %s \n", gettimeofdays() - philo->general->started, philo->id+1, str);
	pthread_mutex_unlock(&philo->mutixes->print);
}
void	ft_usleep(long time)
{
	long	start;

	start = gettimeofdays();
	while (gettimeofdays() - start < time)
		usleep(50);
}

int	check_if_all_philos_ate(t_default *general, t_philo *philos, t_locks *mutixes)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(general->max_of_meals == -1)
		return (0);
	while (i < general->number_philo)
	{
		pthread_mutex_lock(mutixes->meals);
		if ((philos[i]).number_of_meals >= general->max_of_meals)
			j++;
		pthread_mutex_unlock(mutixes->meals);
		i++;
	}
	if (j == general->number_philo)
		return (1);
	return (0);
}

void *philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if(philo->id % 2 != 0)
		ft_usleep(50);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printer(philo,"has taken a left fork ");
		pthread_mutex_lock(philo->right_fork);
		printer(philo,"has taken a right fork ");
		pthread_mutex_lock(&philo->mutixes->last_meal_check);
		philo->last_meal = gettimeofdays();
		pthread_mutex_unlock(&philo->mutixes->last_meal_check);
		printer(philo,"is eating ");
		ft_usleep(philo->general->time_to_eat);
		pthread_mutex_lock(philo->mutixes->meals);
		philo->number_of_meals++;
		pthread_mutex_unlock(philo->mutixes->meals);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printer(philo,"is sleeping ");
		ft_usleep(philo->general->time_to_sleep);
		printer(philo,"is thinking ");
	}
}

void	mutixes_initializer(t_default *general, t_locks *mutixes)
{
	int i = 0;
	while (i < general->number_philo)
	{
		pthread_mutex_init(&mutixes->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutixes->last_meal_check, NULL);
	pthread_mutex_init(&mutixes->print, NULL);
	pthread_mutex_init(mutixes->meals, NULL);
}

void	philo_initializer(t_default *general, t_philo *philos, t_locks *mutixes)
{
	int i;

	i = 0;
	general->started = gettimeofdays();
	while (i < general->number_philo)
	{
		philos[i].id = i;
		philos[i].general = general;
		philos[i].mutixes = mutixes;
		philos[i].left_fork = &mutixes->forks[i];
		if (i == general->number_philo - 1)
			philos[i].right_fork = &mutixes->forks[0];
		else
			philos[i].right_fork = &mutixes->forks[i + 1];
		philos[i].last_meal = gettimeofdays();
		philos[i].number_of_meals = 0;
		pthread_create(&philos[i].philo_thread, NULL, &philosopher, &philos[i]);
		usleep(50);
		i++;
	}
}

int	check_if_philo_went_Metaphysical(t_philo *philos, t_default *general, t_locks *mutixes)
{
	int i;
	
	if(check_if_all_philos_ate(general, philos, mutixes) == 1)
		return (0);
	i = 0;
	long check = 0;
	while (i < general->number_philo)
	{
		pthread_mutex_lock(&mutixes->last_meal_check);
		check = gettimeofdays() - philos[i].last_meal;
		if (check > general->time_to_die)
		{
			pthread_mutex_lock(&mutixes->print);
			printf("%lu %d died\n", gettimeofdays() - general->started, philos[i].id+1);
			return (0);
		}
		pthread_mutex_unlock(&mutixes->last_meal_check);
		i++;
	}
	return (1);
}


void	kill_all_threads(t_philo *philos, t_default *general)
{
	int i;

	i = 0;
	while (i < general->number_philo)
	{
		pthread_detach(philos[i].philo_thread);
		i++;
	}
}


int main(int argc, char **argv)
{
	t_default *general;
	t_philo *philos;
	t_locks *mutixes;
	int i;

	i = 0;
	general = (t_default *)calloc(1, sizeof(t_default));
	if(data_init(&general, argv))
	{
		printf("Error: arguments\n");
		return (1);
	}
	mutixes = (t_locks *)calloc(1,sizeof(t_locks));
	mutixes->forks = (pthread_mutex_t *)calloc(general->number_philo , sizeof(pthread_mutex_t));
	mutixes->meals = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	philos = (t_philo *)calloc(general->number_philo ,  sizeof(t_philo));
	mutixes_initializer(general, mutixes);
	philo_initializer(general, philos, mutixes);
	while (1)
		if(check_if_philo_went_Metaphysical(philos, general, mutixes) == 0)
			break;
	kill_all_threads(philos, general);
}
