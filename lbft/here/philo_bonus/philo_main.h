/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 22:44:30 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:16 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MAIN_H
# define PHILO_MAIN_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>

# define SEM_FORKS "forks"
# define SEM_PRINT "print"
# define SEM_DEAD "dead"
# define SEM_EAT "eat"

typedef struct s_norm
{
	int		i;
	int		*pids;
	pid_t	pid;
	int		status;
}	t_norm;

typedef struct s_philo_info
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_times_each_philo_must_eat;
	long	start_time;
}	t_philo_info;

typedef struct s_data
{
	t_philo_info	*info;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
}	t_data;

typedef struct s_philo
{
	struct timeval	time_last_eat;
	int				id;
	int				num_of_eat;
	int				eat_number;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

void	full_info(int ac, char *av[], t_philo_info *info);
void	check_if_all_inputs_valide(char *av[]);
void	skoutcha(char *str);
long	get_time(void);
void	ft_usleep(long time);
long	ft_atoi(const char *str);
void	print_status(t_philo *philo, char *status);
void	exit_data(char *str);
void	philo_init(t_philo **philo, t_data **data);
long	_data_race_saver(struct timeval time);
void	killing_system(t_philo *philo, t_norm *data);

#endif