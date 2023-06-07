/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:50:43 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/07 17:57:08 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher_routine(t_philo *philo, sem_t *fork, sem_t *print)
{
	while (1)
	{
		ft_actions(philo, 0, fork, print);
		while (philo->data->philos_nb == 1)
			check_end(philo, print, fork);
		ft_actions(philo, 0, fork, print);
		philo->data->eating_times++;
		ft_actions(philo, 1, fork, print);
		philo->eated = get_time();
		ft_sleep(philo->data->time_to_eat, philo, print, fork);
		sem_post(fork);
		sem_post(fork);
		ft_actions(philo, 2, fork, print);
		ft_sleep(philo->data->time_to_sleep, philo, print, fork);
		ft_actions(philo, 3, fork, print);
	}
}

t_philo	*ft_new(t_data *data, long long start_time)
{
	static int		i;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (i == 0)
		i = 1;
	philo->eated = get_time();
	philo->id = i++;
	philo->start_time = start_time;
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

t_data	*ft_new_data(char **av)
{
	t_data			*data;
	sem_t			*print;
	sem_t			*forks;

	sem_unlink("/sem_fork");
	forks = sem_open("/sem_fork", O_CREAT, 0666, ft_atoi(av[1]));
	sem_unlink("/sem_print");
	print = sem_open("/sem_print", O_CREAT,  0666, 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philos_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->eat = ft_atoi(av[5]);
	data->i = 1;
	data->print = print;
	data->forks = forks;
	data->eating_times = 0;
	return (data);
}

int main(int ac, char **av)
{
	t_philo			*philo;
	t_data			*data;
	int				a = 0;
	int				status;

	if (check_av_ac(ac, av))
		return (0);
	else
	{
		data = ft_new_data(av);
		philo = creat_philos(av, data);
		while (data->i <= atoi(av[1]))
		{
			usleep(1000);
			philo->pid = fork();
			if (philo->pid == 0)
			{
				philosopher_routine(philo, data->forks, data->print);
				exit(0);	
			}
			data->i++;
			philo = philo->next;
		}
	}
	data->i = 1;
	while (data->i <= data->philos_nb)
	{
		waitpid(philo->pid, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			kill(0, SIGINT);
			sem_post(data->print);
			exit(5);
		}
		else if (WEXITSTATUS(status) == 1)
			exit(1);
		philo = philo->next;
		data->i++;
	}
	waitpid(0, &status, 0);
	exit(1);
}
