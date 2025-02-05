/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <mabahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:21:42 by mabahani          #+#    #+#             */
/*   Updated: 2023/03/17 14:30:22 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PHILOSOFERS_H
#define PHILO_PHILOSOFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>

typedef struct s_default {
	long started;
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_of_meals;
}	t_default;

typedef struct s_locks{
	pthread_mutex_t *forks;
	pthread_mutex_t print;
	pthread_mutex_t *meals;
	pthread_mutex_t last_meal_check;
}	t_locks;

typedef struct s_philo{
	int id;
	int number_of_meals;
	long last_meal;
	pthread_t philo_thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_default *general;
	t_locks *mutixes;
}	t_philo;

#endif //PHILO_PHILOSOFERS_H
