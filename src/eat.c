/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/22 17:08:23 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_starvation(t_arrays *arrays, t_args *args, int thread_id)
{
	struct timeval current;
    double timestamp;

    gettimeofday(&current, NULL);
	timestamp = ft_time_ms(args->start_time, current);
	if (ft_time_ms(arrays->last_meal[thread_id], current) > args->die_time)
	{
		printf("%.0f: P%d %s", timestamp, thread_id + 1, "is dead\n");
		pthread_mutex_lock(&arrays->death_mutex);
		args->death = true;
		pthread_mutex_unlock(&arrays->death_mutex);
		return (2);
	}
	return (0);
}

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
	ft_print(arrays, args, thread_id, "grabbed first fork\n");//check return 2
	pthread_mutex_lock(&arrays->forks[second]);
	ft_print(arrays, args, thread_id, "grabbed second fork\n");//check return 2
	ft_print(arrays, args, thread_id, "is eating\n");//check return 2
	pthread_mutex_lock(&arrays->meals_mutex[thread_id]);
	arrays->meals[thread_id]++; // separate function
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
			usleep(args->eat_time * 1000 - ate < 5000);
			break ;
		}
		else
			usleep(5000);
		ate += 5000;
	}
	if (ret == 0)
		gettimeofday(&arrays->last_meal[thread_id], NULL);
	pthread_mutex_unlock(&arrays->meals_mutex[thread_id]);
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
