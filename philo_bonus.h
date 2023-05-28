/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:45:10 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/28 22:33:55 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>

typedef struct data{
	int				philos_nb;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	int				is_dead_yet;
	int				i;
	long long		eat;
	sem_t			*fork;
	sem_t			*print;
	int				eating_times;
}				t_data;

typedef struct philo{
	int				id;
	pthread_t		thread;
	long long		start_time;
	long long		eated;
	int				is_alive;
	t_data			*data;
	struct philo	*next;
}t_philo;

long long	get_time(void);
t_data		*ft_new_data(char **av, sem_t print, int *a);
t_philo		*ft_new(t_data *data, long long start_time);
int			ft_sleep(long long sl);
int			ft_atoi(char *str);
int			check_av_ac(int ac, char **av);
void		*philosopher_routine(void	*ar);
void		check_end(t_philo *philo, char **av, t_data *data, int *a);
void		the_destroyer(t_data *data, t_philo *philo);

#endif