/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 18:36:37 by cbuzzini         ###   ########.fr       */
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
/* void    ft_destroy_mutexes_in_struct(pthread_mutex_t )
 {
    int         i;
    t_args      *args;
	t_arrays	*arrays;

    i = 0;
    args = ft_args();
	arrays = ft_arrays();
    while (i < args->nb_philo)
        pthread_mutex_destroy(&arrays->philos[i++].mutex);
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
        pthread_mutex_destroy(&arrays->philos[i++].mutex);
	i = 0;
	while (i < args->nb_philo)
        pthread_mutex_destroy(&arrays->philos[i++].fork);
	//ft_destroy_array_mutexes(arrays->forks);
	//ft_destroy_array_mutexes(arrays->meals_mutex);
	//ft_destroy_array_mutexes(arrays->last_meal_mutex);
	pthread_mutex_destroy(&arrays->print_mutex);
	pthread_mutex_destroy(&arrays->death_mutex);
	//pthread_mutex_destroy(&arrays->start_mutex);
	//pthread_mutex_destroy(&arrays->done_mutex);
}


void ft_join_philos(void)
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
	
	int	ft_free_destroy_return(int ret)
{
	t_arrays      *arrays;
		
	arrays = ft_arrays();
	ft_join_philos();
	pthread_join(arrays->monitor, NULL);
	ft_destroy_mutexes();
	free(arrays->philos);
	return (ret);
}
