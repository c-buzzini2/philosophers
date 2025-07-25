/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/25 10:50:06 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_arrays *arrays, t_args *args, int id, int l_philo)
{
	int		first;
	int		second;
	//struct timeval	current;
	//useconds_t		ate;
	int				ret;
	
	if (id % 2 != 0)
	{
		first = id;
		second = l_philo;
	}
	else
	{
		first = l_philo;
		second = id;
	}
	pthread_mutex_lock(&arrays->philos[first].fork);
	if (ft_print(arrays, id, "grabbed first fork\n") == 2)
	{
		pthread_mutex_unlock(&arrays->philos[first].fork);
		return (2);
	}
	pthread_mutex_lock(&arrays->philos[second].fork);
	pthread_mutex_lock(&arrays->philos[id].mutex);
	arrays->philos[id].last_meal = ft_timestamp_ms();
	if (ft_print(arrays, id, "grabbed second fork\n") == 2
	|| ft_print(arrays, id, "is eating\n") == 2)
	{
		pthread_mutex_unlock(&arrays->philos[first].fork);
		pthread_mutex_unlock(&arrays->philos[second].fork);
		pthread_mutex_unlock(&arrays->philos[id].mutex);
		return (2);
	}
	arrays->philos[id].meals++; // separate function
	pthread_mutex_unlock(&arrays->philos[id].mutex);
	//ate = (ft_timestamp_ms() - ;
	ret = 0;
	while (ft_timestamp_ms() - arrays->philos[id].last_meal < args->eat_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->eat_time - (ft_timestamp_ms() - arrays->philos[id].last_meal) < 5)
		{
			usleep((args->eat_time - (ft_timestamp_ms() - arrays->philos[id].last_meal)) * 1000);
			break ;
		}
		else
			usleep(5000);
	}
	pthread_mutex_unlock(&arrays->philos[first].fork);
	pthread_mutex_unlock(&arrays->philos[second].fork);
	return (ret);
}

int	ft_prepare_to_eat(t_arrays *arrays, t_args *args, int id, int l_philo)
{
	if(id == 0)
		usleep(1);
	if (ft_eat(arrays, args, id, l_philo) == 2)
		return (2);
	else
		return (0);	
}
