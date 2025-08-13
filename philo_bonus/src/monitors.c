/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 12:33:22 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_death_flag(void)
{
	t_philo		*philo;
	
	philo = ft_create_philo();
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->death == true)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		return (2);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return (0);
}

int	ft_mutex_and_thread(t_philo *philo)
{
	if (pthread_mutex_init(&philo->monitor_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	if (pthread_mutex_init(&philo->death_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	if (pthread_create(&philo->monitor, NULL, ft_monitor, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	return (0);
}

static int	ft_check_starvation(t_args *args, t_philo *philo)
{
	long	timestamp;

	while (1)
	{
		timestamp = ft_timestamp_ms();
		pthread_mutex_lock(&philo->monitor_mutex);
		if (philo->done_eating == true)
		{
			pthread_mutex_unlock(&philo->monitor_mutex);
			return (0);
		}
		if (timestamp - philo->last_meal > args->die_time)
		{
			sem_wait(args->print_sem);
			printf("%ld: P%d %s", timestamp, philo->id + 1, "died\n");
			pthread_mutex_unlock(&philo->monitor_mutex);
			pthread_mutex_lock(&philo->death_mutex);
			philo->death = true;
			pthread_mutex_unlock(&philo->death_mutex);
			exit (ft_close_semaphores(2));
		}
		pthread_mutex_unlock(&philo->monitor_mutex);
		usleep(3000);
	}
	return (2);
}

void	*ft_monitor(void *arg)
{
	t_args		*args;
	t_philo		*philo;

	(void)arg;
	args = ft_args();
	philo = ft_create_philo();
	ft_check_starvation(args, philo);
	return (NULL);
}