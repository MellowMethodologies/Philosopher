/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:02:23 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/26 10:58:49 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval  tv;
	long long time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill);
}

t_data *ft_new_data(char **av)
{
	//mutex
	pthread_mutex_t	vars;
	pthread_mutex_t	print;

	//data
	t_data *data;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&vars, NULL);
	pthread_mutex_init(&print, NULL);

	// initing data
	data->philos_nb = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->fifth_arg = 0;
	if (av[5])
	{
		data->eat = atoi(av[5]);
		data->fifth_arg = 1;
	}
	data->is_dead_yet = 0;
	
	//data mutex
	data->vars = vars;
	data->print = print;
	return (data);
}

t_philo	*philo(long long time_to_start)
{
	static int i;
	pthread_mutex_t	fork;
	t_philo *philo = malloc(sizeof(t_philo));

	if (i == 0)
		i = 1;
	if( !philo )
		return (NULL);
	pthread_mutex_init(&fork, NULL);
	philo->id = i++;
	philo->fork = fork;
	philo->eated = get_time();
	philo->time_start = time_to_start;
	return (philo);
}

void	ft_sleep(long sl)
{
	long long time = get_time(); 

	while(get_time() - time < sl)
		usleep(100);
}

int ft_actions(t_data *data, int action)
{
    pthread_mutex_lock(&data->print);
    if (action == 0 && data->is_dead_yet == 0)
		printf("%lld %d has taken a fork\n", get_time() - data->philo->time_start, data->philo->id);
    else if (action == 1 && data->is_dead_yet == 0)
        printf("%lld %d is eating\n", get_time() - data->philo->time_start, data->philo->id);
    else if (action == 2 && data->is_dead_yet == 0)
        printf("%lld %d is sleeping\n", get_time() - data->philo->time_start, data->philo->id);
    else if (action == 3 && data->is_dead_yet == 0)
        printf("%lld %d is thinking\n", get_time() - data->philo->time_start, data->philo->id);
    pthread_mutex_unlock(&data->print);
	return(1);
}

void *philosopher_routine(void	*ar)
{
	t_data *data = (t_data *)ar;
	
	if (data->philo->id % 2 == 0)
		ft_sleep(10);
	while(1)
	{
		//lock forks
		pthread_mutex_lock(&data->philo->fork);
		ft_actions(data, 0);
	
		pthread_mutex_lock(&data->philo->next->fork);
		ft_actions(data, 0);
	
		//last time eated
		pthread_mutex_lock(&data->vars);
		data->philo->eated = get_time();
		pthread_mutex_unlock(&data->vars);
		
		ft_actions(data, 1);
		ft_sleep(data->time_to_eat);
		//unlock forks
		pthread_mutex_unlock(&data->philo->fork);
		pthread_mutex_unlock(&data->philo->next->fork);
		
		//sleep
		ft_actions(data, 2);
		ft_sleep(data->time_to_sleep);

		//think
		ft_actions(data, 3);
	}
	return NULL;
}

t_philo		*creat_philos(char **av, long long time_to_start)
{
	t_philo *philosophers;
	t_philo *tmp;
	int i = 1;
	int nb_philo = atoi(av[1]);

	philosophers = philo(time_to_start);
	tmp = philosophers;
	while (i < nb_philo)
	{
		philosophers->next = philo(time_to_start);
		philosophers = philosophers->next;
		i++;
	}
	philosophers->next = tmp;
	return (tmp);
}

int main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	int i;
	long long time_to_start;
	
	i = 1; 
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	else if (atoi(av[1]) == 0)
		return (0);
	else
	{
		time_to_start = get_time();
		data = ft_new_data(av);
		data->philo = creat_philos(av, time_to_start);
		while (i <= atoi(av[1]))
		{
			pthread_mutex_lock(&data->vars);
			data->philo->eated = get_time();
			pthread_mutex_unlock(&data->vars);
			pthread_create(&data->philo->thread, NULL, philosopher_routine, data);
			data->philo = data->philo->next;
			usleep(100);
			i++;
		}
		while(1)
		{
			usleep(10);
			pthread_mutex_lock(&data->vars);
			if (get_time() - data->philo->eated > data->time_to_die)
			{
				pthread_mutex_unlock(&data->vars);
				data->is_dead_yet = 1;
				pthread_mutex_lock(&data->vars);
				pthread_mutex_lock(&data->print);
				printf("%lld %d died\n", get_time() - data->philo->time_start, data->philo->id);
				pthread_mutex_unlock(&data->vars);
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->vars);
				return 0;
			}
			pthread_mutex_unlock(&data->vars);
			data->philo= data->philo->next;
		}
		i = 1;
		while(i < data->philos_nb)
		{
			pthread_detach(data->philo->thread);
			i++;
			data->philo = data->philo ->next;	
		}
		// i = 1;
		// while(i < samir->data.philos_nb)
		// {
		// 	pthread_mutex_destroy(&samir->fork);
		// 	pthread_mutex_destroy(&samir->data.print);
		// 	pthread_mutex_destroy(&samir->data.vars);
		// 	free(samir);
		// 	samir = samir ->next;
		// 	i++;
		// }
	}
}
