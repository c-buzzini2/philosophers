/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 17:04:42 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_control_turns_2(t_args *args, int i)
{
	pthread_mutex_lock(&args->waiter.waiter_mutex);
	if (args->waiter.kill_waiter == true)
	{
		pthread_mutex_unlock(&args->waiter.waiter_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->waiter.waiter_mutex);
	sem_wait(args->waiter_sem);
	sem_post(args->waiter.philo_sems[i]);
	return (0);
}

void	*ft_control_turns(void *arg)
{
	int		avail_turns;
	int		start;
	int		i;
	t_args	*args;

	(void)arg;
	args = ft_args();
	if (args->nb_philo == 1)
		return (NULL);
	start = 2 % args->nb_philo;
	while (1)
	{
		i = start;
		avail_turns = args->nb_philo / 2;
		while (avail_turns > 0)
		{
			if (ft_control_turns_2(args, i) == 1)
				return (NULL);
			i = (i + 2) % args->nb_philo;
			avail_turns--;
		}
		start = (start + 1) % args->nb_philo;
		usleep(1000);
	}
}

int	ft_thread_waiter(t_waiter *waiter)
{
	if (pthread_create(&waiter->w_thread, NULL, ft_control_turns, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	return (0);
}

int	ft_waiter(t_args *args)
{
	int	ret;

	if (pthread_mutex_init(&args->waiter.waiter_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	ret = ft_thread_waiter(&args->waiter);
	return (ret);
}
