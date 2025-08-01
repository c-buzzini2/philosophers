/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starvation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/01 14:31:32 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//START HERE!!! CHECK STARVATION, THEN GO TO START ROUTINE

int	ft_check_starvation(t_philo *philo)
{
	long		timestamp;
	t_arrays	*arrays;
	t_args 		*args;

	arrays = ft_arrays();
	args = ft_args();
	timestamp = ft_timestamp_ms();
	if (timestamp - philo->last_meal > args->die_time)
	{
		sem_wait(arrays->print_sem);
		printf("%ld: P%d %s", timestamp, philo->id + 1, "died\n");
		// sem_post(arrays->print_sem);
		return (2);
	}
	return (0);
}
