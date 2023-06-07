/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:55:50 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/28 21:09:00 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	if (str[i])
	{
		if (str[i] == '+')
			return (0);
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	check_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
			{
				printf("Error: Wrong argument\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_av_ac(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (check_digit(av))
		return (1);
	i = 1;
	while (av[i])
	{
		if (!ft_atoi(av[i++]))
		{
			printf("Error: Wrong argument\n");
			return (1);
		}
	}
	return (0);
}
