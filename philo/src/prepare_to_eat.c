/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 17:40:40 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_single_philo(t_arrays *arrays, int id)
{
	pthread_mutex_lock(&arrays->philos[id].fork);
	ft_print(arrays, id, "has taken the first fork\n");
	pthread_mutex_unlock(&arrays->philos[id].fork);
	return (2);
}

static void	ft_check_turn(t_arrays *arrays, int id, int l_philo)
{
	while (1)
	{
		pthread_mutex_lock(&arrays->philos[id].turn_mutex);
		if (arrays->philos[id].own_turn == 1)
		{
			pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
			pthread_mutex_lock(&arrays->philos[l_philo].turn_mutex);
			if (arrays->philos[l_philo].own_turn == 0)
				return ;
			pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
		}
		else
			pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
		usleep(100);
	}
}

static int	ft_assign_forks(t_arrays *arrays, int id, int l_philo)
{
	int		first;
	int		second;

	if (id % 2 != 0)
	{
		first = id;
		second = l_philo;
	}
	else
	{
		first = l_philo;
		second = id;
	}
	ft_check_turn(arrays, id, l_philo);
	return (ft_grab_forks(first, second, id, l_philo));
}

int	ft_prepare_to_eat(t_arrays *arrays, int id, int l_philo)
{
	if (id == 0)
	{
		if (id == l_philo)
			return (ft_single_philo(arrays, id));
	}
	if (ft_assign_forks(arrays, id, l_philo) == 2)
		return (2);
	else
		return (0);
}
