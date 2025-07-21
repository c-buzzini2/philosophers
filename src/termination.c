/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 13:13:03 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void    ft_free_arrays(void **array)
{
    int         i;
    t_args      *args;

    i = 0;
    args = ft_args();
    while (i < args->nb_philo)
        free (array[i++]);
} */

void    ft_destroy_mutexes(void)
{
    int         i;
    t_arrays      *arrays;
    t_args      *args;

    i = 0;
    args = ft_args();
    arrays = ft_arrays();
    while (i < args->nb_philo)
	{
        pthread_mutex_destroy(&arrays->forks[i++]);
	}
	i = 0;
	while (i < args->nb_philo)
        pthread_mutex_destroy(&arrays->meals_mutex[i++]);
	pthread_mutex_destroy(&arrays->print_mutex);
}


void ft_join_threads(void)
{
	int			i;
	t_arrays	*arrays;
	t_args		*args;

	i = 0;
	args = ft_args();
	arrays = ft_arrays();
	while (i < args->nb_philo)
	{
		pthread_join(arrays->threads[i], NULL);
		i++;
	}
}

int	ft_free_destroy_return(int ret, bool join_threads)
{
	t_arrays      *arrays;

	if (join_threads)
		ft_join_threads();
    arrays = ft_arrays();
	ft_destroy_mutexes();
	free(arrays->forks);
	free(arrays->threads);
	free(arrays->thread_ids);
	free(arrays->meals);
	free(arrays->meals_mutex);
	return (ret);
}
