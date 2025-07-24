/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 13:01:04 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_arrays *arrays, t_args *args, int thread_id, int l_philo)
{
	int		first;
	int		second;
	//struct timeval	current;
	useconds_t		ate;
	int				ret;
	
	if (thread_id % 2 != 0)
	{
		first = thread_id;
		second = l_philo;
	}
	else
	{
		first = l_philo;
		second = thread_id;
	}
	pthread_mutex_lock(&arrays->forks[first]);
	if (ft_print(arrays, args, thread_id, "grabbed first fork\n") == 2)
	{
		pthread_mutex_unlock(&arrays->forks[first]);
		return (2);
	}
	pthread_mutex_lock(&arrays->forks[second]);
	if (ft_print(arrays, args, thread_id, "grabbed second fork\n") == 2
	|| ft_print(arrays, args, thread_id, "is eating\n") == 2)
	{
		pthread_mutex_unlock(&arrays->forks[first]);
		pthread_mutex_unlock(&arrays->forks[second]);
		return (2);
	}
	pthread_mutex_lock(&arrays->last_meal_mutex[thread_id]);
	gettimeofday(&arrays->last_meal[thread_id], NULL);
	pthread_mutex_unlock(&arrays->last_meal_mutex[thread_id]);
	pthread_mutex_lock(&arrays->meals_mutex[thread_id]);
	arrays->meals[thread_id]++; // separate function
	pthread_mutex_unlock(&arrays->meals_mutex[thread_id]);
	ate = 0;
	ret = 0;
	while (ate / 1000 < args->eat_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->eat_time * 1000 - ate < 5000)
		{
			usleep(args->eat_time * 1000 - ate);
			break ;
		}
		else
			usleep(5000);
		ate += 5000;
	}
	if (ret == 0)
	{
		pthread_mutex_lock(&arrays->last_meal_mutex[thread_id]);
		gettimeofday(&arrays->last_meal[thread_id], NULL);
		pthread_mutex_unlock(&arrays->last_meal_mutex[thread_id]);
	}
	pthread_mutex_unlock(&arrays->forks[second]);
	pthread_mutex_unlock(&arrays->forks[first]);
	return (ret);
}

int	ft_prepare_to_eat(t_arrays *arrays, t_args *args, int thread_id, int l_philo)
{
	if(thread_id == 0)
		usleep(1);
	if (ft_eat(arrays, args, thread_id, l_philo) == 2)
		return (2);
	else
		return (0);	
}
