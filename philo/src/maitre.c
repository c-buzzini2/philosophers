/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maitre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/05 10:58:57 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_control_turns(t_arrays *arrays, t_args *args)
{
	int		i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&arrays->meal_mutex);
		if (args->meal_over == true)
		{
			pthread_mutex_unlock(&arrays->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&arrays->meal_mutex);
		pthread_mutex_lock(&arrays->death_mutex);
		if (args->death == true)
		{
			pthread_mutex_unlock(&arrays->death_mutex);
			return (2);
		}
		pthread_mutex_unlock(&arrays->death_mutex);
		while (i < args->nb_philo)
		{
			if (i % 2 != 0)
			{
				pthread_mutex_lock(&arrays->waiters[i].turn_mutex);
				if (arrays->waiters[i].total_meals % 2 == 0)
				{
					arrays->waiters[i].left_turn = 1;
					arrays->waiters[i].right_turn = 0;	
				}
				else
				{
					arrays->waiters[i].left_turn = 0;
					arrays->waiters[i].right_turn = 1;	
				}
				pthread_mutex_unlock(&arrays->waiters[i].turn_mutex);
			}
			else
			{
				pthread_mutex_lock(&arrays->waiters[i].turn_mutex);
				if (arrays->waiters[i].total_meals % 2 == 0)
				{
					arrays->waiters[i].left_turn = 0;
					arrays->waiters[i].right_turn = 1;	
				}
				else
				{
					arrays->waiters[i].left_turn = 1;
					arrays->waiters[i].right_turn = 0;	
				}
				pthread_mutex_unlock(&arrays->waiters[i].turn_mutex);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	*ft_maitre(void *arg)
{
	t_arrays	*arrays;
	t_args		*args;

	(void)arg;
	arrays = ft_arrays();
	args = ft_args();
	ft_control_turns(arrays, args);
	return (NULL);
}
