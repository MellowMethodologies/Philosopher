/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:50:43 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/28 22:34:14 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_actions(t_philo *philo, int action)
{
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
}

void	taking_forks(t_philo *philo)
{
	ft_actions(philo, 0);
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
		philo->data->eating_times++;
		ft_actions(philo, 1);
		philo->eated = get_time();
		ft_sleep(philo->data->time_to_eat);
		ft_actions(philo, 2);
		ft_sleep(philo->data->time_to_sleep);
		ft_actions(philo, 3);
	}
}

void	check_end(t_philo *philo, char **av, t_data *data, int *a)
{
	while (1)
	{
		if (get_time() - philo->eated > philo->data->time_to_die)
		{
			printf("%lld %d died\n", get_time() - philo->start_time, philo->id);
			*a = 1;
			break ;
		}
		else if (av[5])
		{
			if (data->eating_times >= ft_atoi(av[5]) * ft_atoi(av[1]))
			{
				*a = 1;
				break ;
			}
		}
		philo = philo ->next;
		usleep(100);
	}
}


t_philo	*ft_new(t_data *data, long long start_time)
{
	static int		i;
	sem_t			forks;
	t_philo			*philo;
	pid_t			pid;

	pid = fork();
	if (pid == 0)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (NULL);
		if (i == 0)
			i = 1;
		sem_init(&fork, 1, 1);
		philo->eated = get_time();
		philo->id = i++;
		philo->start_time = start_time;
		philo->data = data;
		return (philo);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (i == 0)
		i = 1;
}

t_philo	*creat_philos(char **av, t_data *data)
{
	t_philo		*philosophers;
	t_philo		*tmp;
	long long	start_time;
	int			i;
	int			nb_philo;

	start_time = get_time();
	nb_philo = ft_atoi(av[1]);
	i = 1;
	philosophers = ft_new(data, start_time);
	tmp = philosophers;
	while (i < nb_philo)
	{
		philosophers->next = ft_new(data, start_time);
		philosophers = philosophers->next;
		i++;
	}
	philosophers->next = tmp;
	return (tmp);
}

t_data	*ft_new_data(char **av, sem_t print, int *a)
{
	t_data			*data;
	sem_t			fork;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	sem_init(&fork, 1, 1);
	sem_init(&print, 1, 1);
	data->philos_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->eat = ft_atoi(av[5]);
	data->i = 1;
	data->eating_times = 0;
	data->is_dead_yet = *a;
	data->fork = fork;
	data->print = print;
	return (data);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_philo			*philo1;
	t_data			*data;
	int				a;
	sem_t			*print;

	a = 0;
	sem_init(&print, 1, 1);
	if (check_av_ac(ac, av))
		return (0);
	else
	{
		data = ft_new_data(av, print, &a);
		philo = creat_philos(av, data);
		while (data->i++ <= ft_atoi(av[1]))
		{
			philo->eated = get_time();
			pthread_create(&philo->thread, NULL, philosopher_routine, philo);
			philo1 = philo;
			pthread_detach(philo1->thread);
			philo = philo ->next;
		}
		check_end(philo, av, data, &a);
		the_destroyer(data, philo);
	}
}
