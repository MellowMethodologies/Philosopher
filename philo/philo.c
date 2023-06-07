/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:02:23 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/05 21:58:33 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_new(t_data *data, long long start_time)
{
	static int		i;
	pthread_mutex_t	fork;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (i == 0)
		i = 1;
	pthread_mutex_init(&fork, NULL);
	philo->eated = get_time();
	philo->id = i++;
	philo->start_time = start_time;
	philo->fork = fork;
	philo->data = data;
	return (philo);
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

t_data	*ft_new_data(char **av, pthread_mutex_t print, int *a)
{
	t_data			*data;
	pthread_mutex_t	vars;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&vars, NULL);
	data->philos_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->eat = ft_atoi(av[5]);
	data->i = 1;
	data->eating_times = 0;
	data->is_dead_yet = *a;
	data->vars = vars;
	data->print = print;
	return (data);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_data			*data;
	int				a;
	pthread_mutex_t	print;

	a = 0;
	pthread_mutex_init(&print, NULL);
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
			pthread_detach(philo->thread);
			// usleep(100);
			philo = philo ->next;
		}
		check_end(philo, av, data, &a);
		the_destroyer(data, philo);
	}
}
