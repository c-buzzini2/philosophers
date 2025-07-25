/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/25 08:37:17 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_starvation(t_arrays *arrays, t_args *args)
{
    long timestamp;
	int		i;
	int		done_eating;

	while (1)
	{
		i = 0;
		done_eating = 0;
		while (i < args->nb_philo)
		{
			timestamp = ft_timestamp_ms();
			pthread_mutex_lock(&arrays->philos[i].mutex);
			if (timestamp - arrays->philos[i].last_meal > args->die_time)
			{
				pthread_mutex_lock(&arrays->print_mutex);
				pthread_mutex_lock(&arrays->death_mutex);
				printf("%ld: P%d %s", timestamp, i + 1, "is dead\n");
				args->death = true;
				pthread_mutex_unlock(&arrays->death_mutex);
				pthread_mutex_unlock(&arrays->print_mutex);
				pthread_mutex_unlock(&arrays->philos[i].mutex);
				return (2);
			}
			if (args->should_eat == arrays->philos[i].meals)
				done_eating++;
			pthread_mutex_unlock(&arrays->philos[i].mutex);
			if (done_eating == args->nb_philo)
				return (0);
			i++;
		}
		usleep(500);
	}
	return (0);
}

void *ft_monitor(void *arg)
{
	t_arrays    *arrays;
    t_args      *args;

	(void)arg;
	arrays = ft_arrays();
    args = ft_args();
	ft_check_starvation(arrays, args);
	return (NULL);
}