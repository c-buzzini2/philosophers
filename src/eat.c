/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/18 17:56:29 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_arrays *arrays, int thread_id, int l_philo) //ADD HOW LONG THEY EAT
{
	double	t1;
	t_args	*args;
	struct timeval end;
	
	args = ft_args();
	gettimeofday(&end, NULL);
	t1 = ft_time_ms(args->start_time, end);
	pthread_mutex_lock(&arrays->forks[thread_id]);
	printf("%.0f: Thread %d (P%d) grabbed right fork\n", t1, thread_id, thread_id + 1);
	pthread_mutex_lock(&arrays->forks[l_philo]);
	printf("%.0f: Thread %d (P%d) grabbed left fork\n", t1, thread_id, thread_id + 1);
	pthread_mutex_lock(&arrays->meals_mutex);
	arrays->meals[thread_id]++;
	printf("%.0f: Thread %d (P%d) is eating (meal %d)\n", t1, thread_id, thread_id + 1, arrays->meals[thread_id]);
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
