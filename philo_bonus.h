/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:45:10 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/06 15:04:10 by sbadr            ###   ########.fr       */
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
# include <signal.h>
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
	int				eating_times;
}				t_data;

typedef struct philo{
	pid_t			pid;
	int				id;
	pthread_t		thread;
	long long		start_time;
	long long		eated;
	int				is_alive;
	t_data			*data;
	struct philo	*next;
}t_philo;

t_philo		*ft_new(t_data *data, long long start_time);
int			ft_atoi(char *str);
int			check_av_ac(int ac, char **av);

#endif