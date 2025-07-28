/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/28 15:46:43 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_single_philo(t_arrays *arrays, int id)
{
	pthread_mutex_lock(&arrays->philos[id].fork);
	ft_print(arrays, id, "has taken the first fork\n");
	pthread_mutex_unlock(&arrays->philos[id].fork);
	return (2);
}

static int	ft_eat(t_arrays *arrays, t_args *args, int id, int l_philo)
{
	int		first;
	int		second;
	int		ret;
	
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
	while (1)
	{
		pthread_mutex_lock(&arrays->philos[id].turn_mutex);
		if(arrays->philos[id].own_turn == 1)
		{
			pthread_mutex_lock(&arrays->philos[l_philo].turn_mutex);
			if(arrays->philos[l_philo].own_turn == 0)
				break ;
			pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
		}
		pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
		usleep(100);
	}
	pthread_mutex_lock(&arrays->philos[first].fork);
	if (ft_print(arrays, id, "has taken the first fork\n") == 2)
	{
		pthread_mutex_unlock(&arrays->philos[first].fork);
		pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
		pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
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
		pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
		pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
		return (2);
	}
	arrays->philos[id].meals++; // separate function
	pthread_mutex_unlock(&arrays->philos[id].mutex);
	arrays->philos[id].own_turn = 0;
	arrays->philos[l_philo].own_turn = 1;
	pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
	pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
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
	{
		if (id == l_philo)
			return (ft_single_philo(arrays, id));
	}
	if (ft_eat(arrays, args, id, l_philo) == 2)
		return (2);
	else
		return (0);	
}
