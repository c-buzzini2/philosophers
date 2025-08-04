/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/04 14:47:31 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_arrays *arrays, int id, int first, int second)
{
	int		ret;
	t_args	*args;

	args = ft_args();
	ret = 0;
	while (ft_timestamp_ms() - arrays->philos[id].last_meal < args->eat_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->eat_time
			- (ft_timestamp_ms() - arrays->philos[id].last_meal) < 5)
		{
			usleep((args->eat_time - (ft_timestamp_ms()
						- arrays->philos[id].last_meal)) * 1000);
			break ;
		}
		else
			usleep(5000);
	}
	pthread_mutex_unlock(&arrays->philos[first].fork);
	pthread_mutex_unlock(&arrays->philos[second].fork);
	return (ret);
}

static int	ft_change_turns(int first, int second, int id, int l_philo)
{
	t_arrays	*arrays;

	arrays = ft_arrays();
	pthread_mutex_lock(&arrays->waiters[id].turn_mutex);
	arrays->waiters[id].total_meals++;
	pthread_mutex_unlock(&arrays->waiters[id].turn_mutex);
	pthread_mutex_lock(&arrays->waiters[l_philo].turn_mutex);
	arrays->waiters[l_philo].total_meals++;
	pthread_mutex_unlock(&arrays->waiters[l_philo].turn_mutex);
	return (ft_eat(arrays, id, first, second));
}

int	ft_grab_forks(int first, int second, int id, int l_philo)
{
	t_arrays	*arrays;

	arrays = ft_arrays();
	pthread_mutex_lock(&arrays->philos[first].fork);
	if (ft_print(arrays, id, "has taken the first fork\n") == 2)
	{
		pthread_mutex_unlock(&arrays->philos[first].fork);
		return (2);
	}
	pthread_mutex_lock(&arrays->philos[second].fork);
	pthread_mutex_lock(&arrays->philos[id].mutex);
	arrays->philos[id].last_meal = ft_timestamp_ms();
	if (ft_print(arrays, id, "has taken the second fork\n") == 2
		|| ft_print(arrays, id, "is eating\n") == 2)
	{
		pthread_mutex_unlock(&arrays->philos[first].fork);
		pthread_mutex_unlock(&arrays->philos[second].fork);
		pthread_mutex_unlock(&arrays->philos[id].mutex);
		return (2);
	}
	arrays->philos[id].meals++;
	pthread_mutex_unlock(&arrays->philos[id].mutex);
	return (ft_change_turns(first, second, id, l_philo));
}
