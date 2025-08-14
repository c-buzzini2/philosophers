/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/14 11:00:51 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_single_philo(t_philo *philo)
{
	t_args			*args;

	args = ft_args();
	ft_print(philo, "has taken the first fork\n");
	usleep(args->die_time * 3000);
	exit (ft_close_semaphores(2));
}

long	ft_timestamp_ms(void)
{
	t_args			*args;
	struct timeval	current;

	args = ft_args();
	gettimeofday(&current, NULL);
	return ((current.tv_sec - args->start_time.tv_sec) * 1000
		+ (current.tv_usec - args->start_time.tv_usec) / 1000.0);
}

int	ft_start_routine(t_philo *philo)
{
	t_args		*args;

	args = ft_args();
	if (args->nb_philo == 1)
		return (ft_single_philo(philo));
	while (1)
	{
		ft_grab_forks(philo);
		if (philo->meals == args->should_eat)
		{
			pthread_mutex_lock(&philo->monitor_mutex);
			philo->done_eating = true;
			pthread_mutex_unlock(&philo->monitor_mutex);
			exit (ft_close_semaphores(0));
		}
		ft_sleep_and_think(philo, args);
	}
}
