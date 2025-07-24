/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 13:31:00 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double ft_time_ms(struct timeval start, struct timeval end)
{
    return ((end.tv_sec - start.tv_sec) * 1000 + 
           (end.tv_usec - start.tv_usec) / 1000.0);
}

void *ft_start_routine(void *arg)
{
	int	        thread_id;
	t_arrays    *arrays;
    int         l_philo;
    t_args      *args;

	thread_id = *(int*)arg;
	arrays = ft_arrays();
    args = ft_args();
    l_philo = thread_id - 1;
    if (l_philo == -1)
    {
        l_philo = args->nb_philo - 1;
    }
    if (args->should_eat == 0)
        return (NULL);
    usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&arrays->start_mutex);
        if (args->can_start == true)  // This is false initially
        {
            pthread_mutex_unlock(&arrays->start_mutex);
            break;
        }
        pthread_mutex_unlock(&arrays->start_mutex);
        usleep(100);
    }
    
    while (1)
    {
        if (ft_prepare_to_eat(arrays, args, thread_id, l_philo) == 2)
            break ;
        if (arrays->meals[thread_id] == args->should_eat)
        {
            pthread_mutex_lock(&arrays->done_mutex);
            args->done_eating++;
            pthread_mutex_unlock(&arrays->done_mutex);
            break ;
        }
        if (ft_check_death_flag() == 2 ||
        ft_sleep_and_think(arrays, args, thread_id) == 2||
        ft_check_death_flag() == 2)
            break ; 
    }
	return (NULL);
}
