/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 13:08:47 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat_even(t_arrays *arrays, int thread_id, int l_philo) //ADD HOW LONG THEY EAT
{
	t_args	*args;
	
	args = ft_args();
	pthread_mutex_lock(&arrays->forks[l_philo]);
	ft_print(arrays, args, thread_id, "grabbed left fork\n");
	pthread_mutex_lock(&arrays->forks[thread_id]);
	ft_print(arrays, args, thread_id, "grabbed right fork\n");
	pthread_mutex_lock(&arrays->meals_mutex[thread_id]);
	arrays->meals[thread_id]++;
	ft_print(arrays, args, thread_id, "is eating\n");
	usleep(args->eat_time * 1000);
	pthread_mutex_unlock(&arrays->meals_mutex[thread_id]);
	pthread_mutex_unlock(&arrays->forks[thread_id]);
	pthread_mutex_unlock(&arrays->forks[l_philo]);
}

static void	ft_eat_odd(t_arrays *arrays, int thread_id, int l_philo) //ADD HOW LONG THEY EAT
{
	t_args	*args;
	
	args = ft_args();
	pthread_mutex_lock(&arrays->forks[thread_id]);
	ft_print(arrays, args, thread_id, "grabbed right fork\n");
	pthread_mutex_lock(&arrays->forks[l_philo]);
	ft_print(arrays, args, thread_id, "grabbed left fork\n");
	pthread_mutex_lock(&arrays->meals_mutex[thread_id]);
	arrays->meals[thread_id]++;
	ft_print(arrays, args, thread_id, "is eating\n");
	usleep(args->eat_time * 1000);
	pthread_mutex_unlock(&arrays->meals_mutex[thread_id]);
	pthread_mutex_unlock(&arrays->forks[l_philo]);
	pthread_mutex_unlock(&arrays->forks[thread_id]);
}

void	ft_prepare_to_eat(t_arrays *arrays, int thread_id, int l_philo)
{
	if(thread_id == 0)
		usleep(1);
	if (thread_id % 2 != 0)
    {
		ft_eat_odd(arrays, thread_id, l_philo);
    }
	if (thread_id % 2 == 0)
    {
		ft_eat_even(arrays, thread_id, l_philo);
    }
	//ft_sleep
	
}

/* void	ft_prepare_to_eat(t_arrays *arrays, int thread_id, int r_philo, int l_philo)
{
	int r_meals;
	int l_meals;
	int my_meals;
	struct timeval meal_start;

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
	
} */
