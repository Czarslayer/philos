/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <mabahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:01:53 by mabahani          #+#    #+#             */
/*   Updated: 2023/03/17 21:45:01 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}

void	printer(t_philo *philo, char *str, t_sems *locks, long started)
{
	sem_wait(locks->print);
	printf("%lu %d %s \n", get_current_time() - started, philo->id, str);
	sem_post(locks->print);
}

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
	if(arg_checker_zero((*def)->number_philo, (*def)->time_to_die, \
		(*def)->time_to_eat, (*def)->time_to_sleep) == 1)
		return (1);
	return (0);
}

int init_philo(t_philo **philo, int number_philo)
{
	int i;

	i = 0;
	while (i < number_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].meals = 0;
		(*philo)[i].last_meal = 0;
		i++;
	}
	return (0);
}

int init_sems(t_sems **locks, int number_philo)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("meals");
	sem_unlink("last_meal_check");
	(*locks)->forks = sem_open("forks", O_CREAT, 0644, number_philo);
	(*locks)->print = sem_open("print", O_CREAT, 0644, 1);
	(*locks)->meals = sem_open("meals", O_CREAT, 0644, 1);
	(*locks)->last_meal_check = sem_open("last_meal_check", O_CREAT, 0644, 1);
	if ((*locks)->forks == SEM_FAILED || (*locks)->print == SEM_FAILED || \
		(*locks)->meals == SEM_FAILED || (*locks)->last_meal_check == SEM_FAILED)
		return (1);
	return (0);
}

void	philo_routine(t_philo *philo, t_default *def, t_sems *locks)
{	
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while(1)
	{
		sem_wait(locks->forks);
		printer(philo, "has taken a first fork", locks, def->started);
		sem_wait(locks->forks);
		printer(philo, "has taken a second fork", locks, def->started);
		sem_wait(locks->last_meal_check);
		philo->last_meal = get_current_time();
		sem_post(locks->last_meal_check);
		printer(philo, "is eating", locks, def->started);
		ft_usleep(def->time_to_eat);
		sem_post(locks->forks);
		sem_post(locks->forks);
		philo->meals++;
		printer(philo, "is sleeping", locks, def->started);
		ft_usleep(def->time_to_sleep);
		printer(philo, "is thinking", locks, def->started);
	}
}

void	shinigami(int	*pids, int numberphilo, t_sems *locks)
{
	int i;

	i = 0;
	while (i < numberphilo)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	sem_close(locks->forks);
	sem_close(locks->print);
	sem_close(locks->meals);
	sem_close(locks->last_meal_check);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("meals");
	sem_unlink("last_meal_check");
}

int main(int ac,char **av)
{
	t_philo *philo;
	t_default *def;
	t_sems *locks;
	int *pids;
	int pid;
	int i = 0;
	int j = 0;

	if (ac < 5 || ac > 6)
		return (1);
	def = malloc(sizeof(t_default));
	if (data_init(&def, av) == 1)
		return (1);
	locks = malloc(sizeof(t_sems));
	philo = malloc(sizeof(t_philo) * def->number_philo);
	pids = malloc(sizeof(int) * def->number_philo);
	if (init_sems(&locks, def->number_philo) == 1)
		return (1);
	if(init_philo(&philo, def->number_philo) == 1)
		return (1);
	def->started = get_current_time();
	while(i < def->number_philo)
	{
		pid = fork();
		if (pid == 0)
			philo_routine(&philo[i], def, locks);
		else
		{
			pids[i] = pid;
			i++;
		}
	}
	if(waitpid(-1, NULL, 0) == -1)
		shinigami(pids, def->number_philo, locks);
	return (0);
}