/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 11:19:25 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_eat(t_philo *philo)
{
	int		ret;
	t_args	*args;

	args = ft_args();
	ret = 0;
	while (ft_timestamp_ms() - philo->last_meal < args->eat_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->eat_time
			- (ft_timestamp_ms() - philo->last_meal) < 5)
		{
			usleep((args->eat_time - (ft_timestamp_ms()
						- philo->last_meal)) * 1000);
			break ;
		}
		else
			usleep(5000);
	}
	sem_post(args->waiter_sem);
	return (ret);
}

int	ft_grab_forks(t_philo *philo)
{
	if (ft_check_death_flag() == 2)
		return (2);
	sem_wait(philo->turn_sem);
	if (ft_print(philo, "has taken the first fork\n") == 2
			|| ft_print(philo, "has taken the second fork\n") == 2
			|| ft_print(philo, "is eating\n") == 2)
		return (2);
	pthread_mutex_lock(&philo->monitor_mutex);
	philo->last_meal = ft_timestamp_ms();
	pthread_mutex_unlock(&philo->monitor_mutex);
	philo->meals++;
	return (ft_eat(philo));
}
