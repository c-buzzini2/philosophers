/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:52 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/16 14:03:42 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_start_routine(void *arg)
{
	int	thread_id;
	t_arrays *arrays;

	thread_id = *(int*)arg;
	arrays = ft_arrays();
	pthread_mutex_lock(&arrays->forks[thread_id]);
	printf("thread %d\n", thread_id);
	pthread_mutex_unlock(&arrays->forks[thread_id]);
	return (NULL);
}
//START HERE!!!
int	ft_thread(t_args *args, t_arrays *arrays)
{
	int	i;
    int thread_ids[3] = {1, 2, 3};//allocate according to number of philos as well


	i = 0;
	arrays->threads = malloc((args->nb_philo) * sizeof(pthread_t));
	if (arrays->threads == NULL)
	{
		ft_puterror("Allocation error");
		//destroy mutex
		//free array forks
		exit (1);
	}
	//start counting time
	while (i < args->nb_philo)
	{
		if (pthread_create(&arrays->threads[i], NULL, ft_start_routine, &i) != 0)//does &1 start a race condition?
		{
			ft_puterror("Could not initialize mutex");
			//destroy mutex
			//free array forks
			//destroy threads up to this point (use while j < i) how???
			//free array of threads
			exit (1);
		}
		i++;
	}
	return (0);//?
}

int	ft_mutex_and_thread(t_args *args, t_arrays *arrays)
{
	int	i;

	i = 0;
	arrays->forks = malloc((args->nb_philo) * sizeof(pthread_mutex_t));
	if (arrays->forks == NULL)
	{
		ft_puterror("Allocation error");
		exit (1);
	}
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->forks[i], NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			//destroy mutex up to this point (use while j < i)
			//free array of forks
			exit (1);
		}
		i++;
	}
	ft_thread(args, arrays);
	return (0);//?
}

t_args	*ft_args(void)
{
	static	t_args args;
	
	return (&args);
}

t_arrays	*ft_arrays(void)
{
	static	t_arrays arrays;
	
	return (&arrays);
}

int main (int argc, char **argv)
{
	t_args *args;
	t_arrays *arrays;

	args = ft_args();
	arrays = ft_arrays();
	ft_parse_args(args, argc, argv);
    ft_mutex_and_thread(args, arrays);
	
	free(arrays->forks);
	free(arrays->threads);
}