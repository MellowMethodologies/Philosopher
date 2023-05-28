/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:14:42 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/28 18:37:24 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_actions(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->print);
	if (action == 0)
	{
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
	pthread_mutex_unlock(&philo->data->print);
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_actions(philo, 0);
	pthread_mutex_lock(&philo->next->fork);
	ft_actions(philo, 0);
}

void	*philosopher_routine(void	*ar)
{
	t_philo	*philo;

	philo = (t_philo *)ar;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->data->is_dead_yet == 1)
			return (NULL);
		taking_forks(philo);
		pthread_mutex_lock(&philo->data->vars);
		philo->data->eating_times++;
		pthread_mutex_unlock(&philo->data->vars);
		ft_actions(philo, 1);
		pthread_mutex_lock(&philo->data->vars);
		philo->eated = get_time();
		pthread_mutex_unlock(&philo->data->vars);
		ft_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_actions(philo, 2);
		ft_sleep(philo->data->time_to_sleep);
		ft_actions(philo, 3);
	}
}

void	check_end(t_philo *philo, char **av, t_data *data, int *a)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->vars);
		if (get_time() - philo->eated > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%lld %d died\n", get_time() - philo->start_time, philo->id);
			*a = 1;
			pthread_mutex_unlock(&philo->data->vars);
			break ;
		}
		else if (av[5])
		{
			if (data->eating_times >= ft_atoi(av[5]) * ft_atoi(av[1]))
			{
				pthread_mutex_lock(&philo->data->print);
				*a = 1;
				pthread_mutex_unlock(&philo->data->vars);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->data->vars);
		philo = philo ->next;
		usleep(100);
	}
}
