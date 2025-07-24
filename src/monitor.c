/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 15:37:13 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_starvation(t_arrays *arrays, t_args *args)
{
	struct timeval current;
    double timestamp;
	int		i;

	while (1)
	{
		i = 0;
		while (i < args->nb_philo)
		{
			gettimeofday(&current, NULL);
			pthread_mutex_lock(&arrays->last_meal_mutex[i]);
			if (ft_time_ms(arrays->last_meal[i], current) > args->die_time)
			{
				pthread_mutex_unlock(&arrays->last_meal_mutex[i]);
				timestamp = ft_time_ms(args->start_time, current);
				pthread_mutex_lock(&arrays->print_mutex);
				printf("%.0f: P%d %s", timestamp, i + 1, "is dead\n");
				pthread_mutex_lock(&arrays->death_mutex);
				args->death = true;
				pthread_mutex_unlock(&arrays->death_mutex);
				pthread_mutex_unlock(&arrays->print_mutex);
				return (2);
			}
			pthread_mutex_unlock(&arrays->last_meal_mutex[i]);
			pthread_mutex_lock(&arrays->done_mutex);
			if (args->done_eating == args->nb_philo)
			{
				pthread_mutex_unlock(&arrays->done_mutex);
				break ;
			}
			pthread_mutex_unlock(&arrays->done_mutex);
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