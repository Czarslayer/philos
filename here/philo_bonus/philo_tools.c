/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:13:24 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:37 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_main.h"

void	killing_system(t_philo *philo, t_norm *data)
{
	int	i;

	i = 0;
	if (WIFEXITED(data->status))
	{
		if (WEXITSTATUS(data->status) == 1)
		{
			while (i < philo->data->info->num_of_philo)
				kill(data->pids[i++], SIGKILL);
			exit(1);
		}
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	sem_wait(philo->data->print);
	time = get_time() - philo->data->info->start_time;
	printf("%ld %d %s \n", time, philo->id + 1, status);
	sem_post(philo->data->print);
}

long	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		else if (result > 9223372036854775807 && sign == -1)
			return (0);
	}
	return ((result * sign));
}
