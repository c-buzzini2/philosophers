/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/18 16:36:46 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_arrays *arrays, int thread_id, int l_philo)
{
	pthread_mutex_lock(&arrays->forks[thread_id]);
	printf("Thread %d (P%d) grabbed right fork\n", thread_id, thread_id + 1);
	pthread_mutex_lock(&arrays->forks[l_philo]);
	printf("Thread %d (P%d) grabbed left fork\n", thread_id, thread_id + 1);
	pthread_mutex_lock(&arrays->meals_mutex);
	arrays->meals[thread_id]++;
	printf("Thread %d (P%d) is eating (meal %d)\n",thread_id, thread_id + 1, arrays->meals[thread_id]);
	pthread_mutex_unlock(&arrays->meals_mutex);
	pthread_mutex_unlock(&arrays->forks[l_philo]);
	pthread_mutex_unlock(&arrays->forks[thread_id]);
}

void	ft_prepare_to_eat(t_arrays *arrays, int thread_id, int r_philo, int l_philo)
{
	int r_meals;
	int l_meals;
	int my_meals;
	
	while (1)
	{
        pthread_mutex_lock(&arrays->meals_mutex);
        r_meals = arrays->meals[r_philo];
        l_meals = arrays->meals[l_philo];
        my_meals =  arrays->meals[thread_id];
        pthread_mutex_unlock(&arrays->meals_mutex);
		if ((thread_id % 2 != 0 && r_meals == my_meals
            && l_meals == my_meals)
            || (thread_id % 2 == 0 && l_philo != 0 && r_meals == my_meals + 1
            && l_meals == my_meals + 1)
			|| (thread_id % 2 == 0 && r_philo == 0 && l_meals == my_meals + 1))
        {
			ft_eat(arrays, thread_id, l_philo);
			my_meals++;
            break;
        }
        usleep(500);
	}
	//ft_sleep
	
}
