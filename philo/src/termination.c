/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/04 13:56:21 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(void)
{
	int			i;
	t_arrays	*arrays;
	t_args		*args;

	i = 0;
	args = ft_args();
	arrays = ft_arrays();
	while (i < args->nb_philo)
		pthread_mutex_destroy(&arrays->philos[i++].mutex);
	i = 0;
	while (i < args->nb_philo)
		pthread_mutex_destroy(&arrays->philos[i++].fork);
	i = 0;
	while (i < args->nb_philo)
		pthread_mutex_destroy(&arrays->waiters[i++].turn_mutex);
	pthread_mutex_destroy(&arrays->print_mutex);
	pthread_mutex_destroy(&arrays->death_mutex);
}

void	ft_join_philos(void)
{
	int			i;
	t_arrays	*arrays;
	t_args		*args;

	i = 0;
	args = ft_args();
	arrays = ft_arrays();
	while (i < args->nb_philo)
		pthread_join(arrays->philos[i++].thread, NULL);
}

void	ft_free_arrays(void)
{
	t_arrays	*arrays;

	arrays = ft_arrays();
	free(arrays->philos);
	free(arrays->waiters);
}

int	ft_free_destroy_return(int ret)
{
	t_arrays	*arrays;

	arrays = ft_arrays();
	ft_join_philos();
	pthread_join(arrays->monitor, NULL);
	pthread_join(arrays->maitre, NULL);
	ft_destroy_mutexes();
	ft_free_arrays();
	return (ret);
}
