/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 13:11:52 by cbuzzini         ###   ########.fr       */
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
    // int         r_philo;
    int         l_philo;
    t_args      *args;

	thread_id = *(int*)arg;
	arrays = ft_arrays();
    args = ft_args();
    // r_philo = thread_id + 1;
    // if (r_philo == args->nb_philo)
    //     r_philo = 0;
    l_philo = thread_id - 1;
    if (l_philo == -1)
    {
        l_philo = args->nb_philo - 1;
    }
	ft_prepare_to_eat(arrays, thread_id, l_philo);
	return (NULL);
}
