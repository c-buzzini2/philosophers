/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/23 14:31:24 by cbuzzini         ###   ########.fr       */
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

