/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/04 14:51:17 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_create_maitre(t_arrays *arrays)
{
	if (pthread_create(&arrays->maitre, NULL, ft_maitre, NULL) != 0)
	{
		ft_puterror("Could not create thread");
		ft_join_philos();
		pthread_join(arrays->monitor, NULL);
		ft_destroy_mutexes();
		ft_free_arrays();
		exit (1);
	}
}

static void	ft_create_monitor(t_arrays *arrays)
{
	if (pthread_create(&arrays->monitor, NULL, ft_monitor, NULL) != 0)
	{
		ft_puterror("Could not create thread");
		ft_join_philos();
		ft_destroy_mutexes();
		ft_free_arrays();
		exit (1);
	}
}

void	ft_threads(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	gettimeofday(&args->start_time, NULL);
	while (i < args->nb_philo)
	{
		if (pthread_create(&arrays->philos[i].thread, NULL, ft_start_routine,
				&arrays->philos[i].id) != 0)
		{
			ft_puterror("Could not create thread");
			j = 0;
			while (j < i)
				pthread_join(arrays->philos[j++].thread, NULL);
			ft_destroy_mutexes();
			ft_free_arrays();
			exit (1);
		}
		i++;
	}
	ft_create_monitor(arrays);
	ft_create_maitre(arrays);
}
