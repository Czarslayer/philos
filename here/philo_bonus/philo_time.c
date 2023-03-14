/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrajiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:12:01 by aerrajiy          #+#    #+#             */
/*   Updated: 2023/02/05 21:42:24 by aerrajiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_main.h"

long	_data_race_saver(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(50);
}
