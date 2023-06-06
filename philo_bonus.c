/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:50:43 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/06 21:00:12 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		// sem_wait(print);
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
	data->eating_times = 0;
	return (data);
}

int main(int ac, char **av)
{
    t_philo         *philo;
    t_data          *data;
    pid_t           pid;
	int i = 1;
	int a = 0;
    int             status;
	sem_t			*print;
	sem_t			*forks;

	sem_unlink("/sem_fork");
	forks = sem_open("/sem_fork", O_CREAT, 0666, ft_atoi(av[1]));
	sem_unlink("/sem_print");
	print = sem_open("/sem_print", O_CREAT,  0666, 1);

    if (check_av_ac(ac, av))
        return (0);
    else
    {
        data = ft_new_data(av);
        philo = creat_philos(av, data);
        while (i <= atoi(av[1]))
        {
            philo->pid = fork();
            if (philo->pid == 0)
				philosopher_routine(philo, forks, print);
			i++;
            philo = philo->next;
        }
	}
	i = 1;
    while (i <= atoi(av[1]) && a != -1)
	{
		waitpid(philo->pid, &status, 0);
		if (WIFEXITED(status) == 1)
		{
			puts("hello");
			a++;
		}
		else if (WIFEXITED(status) == 0){
			a = -1;}
		if (a == data->eat)
		{
			exit(0);
		}
		i++;
		philo = philo->next;
	}
	waitpid(-1, &status, 0);
}
