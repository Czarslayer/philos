/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabahani <mabahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:01:50 by mabahani          #+#    #+#             */
/*   Updated: 2023/03/17 19:36:54 by mabahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_default {
	long started;
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_of_meals;
}	t_default;

typedef struct s_sems {
	sem_t *forks;
	sem_t *print;
	sem_t *meals;
	sem_t *last_meal_check;
}	t_sems;

typedef struct s_philo {
	int id;
	int meals;
	long last_meal;
}	t_philo;

#endif