/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:37:52 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:21 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"

typedef struct s_philo_info
{
	long	start_time;
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philo_eat;
}	t_philo_info;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	*meals;
	pthread_mutex_t	last_meal_check;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal;
	int				maels;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_info	info;
	t_data			*data;
}	t_philo;

long	ft_atoi(char *str);
void	ft_print(char *str, t_philo *philo, char *color);
void	sleep_and_think(t_philo *philo);
void	*routine(void *act_philo);
int		init_data_mutex(t_data **data, t_philo_info *info);
int		run_data_philo(t_philo **philo, t_data **data, t_philo_info *info);
int		check_if_all_inputs_valide(char *av[]);
int		full_philo_info(int ac, char *av[], t_philo_info *info);
long	get_time(void);
void	ft_usleep(long time);
int		the_god_of_death(t_philo *philo);
#endif