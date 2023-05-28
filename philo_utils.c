/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:54:31 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/28 20:52:09 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill);
}

int	ft_sleep(long long sl)
{
	long long	time;

	time = get_time();
	while (get_time() - time < sl)
		usleep(300);
	return (0);
}

void	the_destroyer(t_data *data, t_philo *philo)
{
	data->i = 1;
	while (data->i <= data->philos_nb)
	{
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->data->print);
		pthread_mutex_destroy(&philo->data->vars);
		philo = philo ->next;
		data->i++;
	}
}
