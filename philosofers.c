/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <mabahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:21:42 by mabahani          #+#    #+#             */
/*   Updated: 2023/03/15 00:27:43 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofers.h"

void data_init(t_def **def, char **argv)
{
	(*def)->number_philo = atoi(argv[1]);
	(*def)->time_to_die = atoi(argv[2]);
	(*def)->time_to_eat = atoi(argv[3]);
	(*def)->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		(*def)->number_of_philo_eat = atoi(argv[5]);
	else
		(*def)->number_of_philo_eat = -1;
}

void data_printer(t_def *def)
{
	printf("number_philo: %d\n", def->number_philo);
	printf("time_to_die: %d\n", def->time_to_die);
	printf("time_to_eat: %d\n", def->time_to_eat);
	printf("time_to_sleep: %d\n", def->time_to_sleep);
	printf("number_of_philo_eat: %d\n", def->number_of_philo_eat);
}

double gettimeofdays(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}



int main(int argc, char **argv)
{
	t_def *def;
	t_philo *philos;
	int i;

	i = 0;
	def = (t_def *)calloc(1, sizeof(t_def));
	data_init(&def, argv);
	data_printer(def);
	philos = (t_philo *)calloc(1, sizeof(t_philo) * def->number_philo);
	printf("%.6f\n", gettimeofdays());
}
