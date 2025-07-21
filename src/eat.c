/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 15:11:51 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	ft_check_starvation(t_arrays *arrays, t_args *args, int thread_id, int l_philo)
// {
	
// }

static void	ft_eat(t_arrays *arrays, t_args *args, int thread_id, int l_philo)
{
	int		first;
	int		second;
	
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
	ft_print(arrays, args, thread_id, "grabbed first fork\n");
	pthread_mutex_lock(&arrays->forks[second]);
	ft_print(arrays, args, thread_id, "grabbed second fork\n");
	ft_print(arrays, args, thread_id, "is eating\n");
	pthread_mutex_lock(&arrays->meals_mutex[thread_id]);
	arrays->meals[thread_id]++;
	usleep(args->eat_time * 1000);
	pthread_mutex_unlock(&arrays->meals_mutex[thread_id]);
	pthread_mutex_unlock(&arrays->forks[second]);
	pthread_mutex_unlock(&arrays->forks[first]);
}

void	ft_prepare_to_eat(t_arrays *arrays, t_args *args, int thread_id, int l_philo)
{
	if(thread_id == 0)
		usleep(1);
	ft_eat(arrays, args, thread_id, l_philo);	
}
