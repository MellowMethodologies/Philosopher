/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:56:34 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/07 17:57:13 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill);
}

void	check_end(t_philo *philo, sem_t *print, sem_t *fork)
{
	int	i;

	i = 0;	
	if (philo ->data->philos_nb % 2)
		i = 10;
	if (get_time() - philo->eated > philo->data->time_to_die - i)
	{
		sem_wait(print);
		printf("%lld %d died\n", get_time() - philo->start_time, philo->id);
		exit(0);
	}
	else if (philo->data->eat && philo->data->eating_times > philo->data->eat)
	{
		sem_wait(print);
		sem_post(fork);
		sem_post(fork);
		exit(1);
	}
}

void	ft_sleep(long long sl, t_philo *philo, sem_t *print, sem_t *fork)
{
	long long	time;

	time = get_time();
	while (get_time() - time < sl)
	{
		check_end(philo, print, fork);
		usleep(100);
	}
}

void	ft_actions(t_philo *philo, int action, sem_t *fork, sem_t *print)
{
	sem_wait(print);
	if (action == 0)
	{
		sem_wait(fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->start_time,
			philo->id);
	}
	else if (action == 1)
		printf("%lld %d is eating\n", get_time() - philo->start_time, philo->id);
	else if (action == 2)
		printf("%lld %d is sleeping\n", get_time() - philo->start_time,
			philo->id);
	else if (action == 3)
		printf("%lld %d is thinking\n", get_time() - philo->start_time,
			philo->id);
	sem_post(print);
}