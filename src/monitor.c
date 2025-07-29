/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 15:36:34 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_starvation2(t_arrays *arrays, t_args *args, int i)
{
	long	timestamp;

	timestamp = ft_timestamp_ms();
	pthread_mutex_lock(&arrays->philos[i].mutex);
	if (timestamp - arrays->philos[i].last_meal > args->die_time)
	{
		pthread_mutex_lock(&arrays->death_mutex);
		args->death = true;
		pthread_mutex_unlock(&arrays->death_mutex);
		pthread_mutex_lock(&arrays->print_mutex);
		printf("%ld: P%d %s", timestamp, i + 1, "died\n");
		pthread_mutex_unlock(&arrays->print_mutex);
		pthread_mutex_unlock(&arrays->philos[i].mutex);
		return (2);
	}
	return (0);
}

int	ft_check_starvation(t_arrays *arrays, t_args *args)
{
	int		i;
	int		done_eating;

	while (1)
	{
		i = 0;
		done_eating = 0;
		while (i < args->nb_philo)
		{
			if (ft_check_starvation2(arrays, args, i) == 2)
				return (2);
			if (args->should_eat == arrays->philos[i].meals)
				done_eating++;
			pthread_mutex_unlock(&arrays->philos[i].mutex);
			if (done_eating == args->nb_philo)
				return (0);
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_arrays	*arrays;
	t_args		*args;

	(void)arg;
	arrays = ft_arrays();
	args = ft_args();
	ft_check_starvation(arrays, args);
	return (NULL);
}
