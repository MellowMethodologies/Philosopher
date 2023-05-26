/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:45:10 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/26 11:01:43 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct philo{
	int id;
	pthread_mutex_t fork;
	pthread_t 		thread;
	long long	    time_start;
    long long		eated;
	struct philo *next;
}t_philo;

typedef struct data{
	int 			philos_nb;
	int				fifth_arg;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	int				is_dead_yet;
	long long		eat;
	pthread_mutex_t print;
	pthread_mutex_t vars;
	t_philo			*philo;
}				t_data;


#endif

	// while(1)
		// {
		// 	usleep(10);
		// 	pthread_mutex_lock(&samir->data.vars);
		// 	if (get_time() - samir->eated > samir->data.time_to_die)
		// 	{
		// 		if (!samir->data.is_dead_yet)
		// 		{
		// 			// pthread_mutex_lock(&samir->data.vars);
		// 			samir->data.is_dead_yet = 1;
		// 			pthread_mutex_unlock(&samir->data.vars);
		// 			samir = samir->next;
		// 		}
		// 		pthread_mutex_lock(&samir->data.print);
		// 		printf("%lld %d died\n", get_time() - samir->time_start, samir->id);
		// 		pthread_mutex_unlock(&samir->data.print);
		// 		// pthread_mutex_unlock(&samir->data.vars);
		// 		return 0;
		// 	}
		// 	// pthread_mutex_unlock(&samir->data.vars);
		// 	samir= samir->next;
		// }