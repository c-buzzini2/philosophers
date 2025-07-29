/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 15:58:38 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_create_monitor(t_arrays *arrays)
{
	if (pthread_create(&arrays->monitor, NULL, ft_monitor, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		ft_join_philos();
		ft_destroy_mutexes();
		free(arrays->philos);
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
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_join(arrays->philos[j++].thread, NULL);
			ft_destroy_mutexes();
			free(arrays->philos);
			exit (1);
		}
		i++;
	}
	ft_create_monitor(arrays);
}
