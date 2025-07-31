/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 15:36:30 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//START HERE!!! CHECK STARVATION, THEN GO TO START ROUTINE

static int	ft_check_starvation(t_arrays *arrays, t_args *args, int id)
{
	long	timestamp;

	timestamp = ft_timestamp_ms();
	if (timestamp - arrays->philos[id].last_meal > args->die_time)
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
