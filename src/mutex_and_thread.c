/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 13:23:18 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_meals_mutex(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	arrays->meals_mutex = malloc((args->nb_philo) * sizeof(pthread_mutex_t));
	if (arrays->meals_mutex == NULL)
	{
		ft_puterror("Allocation error"); //what else should I clean here
		exit (1);//clean everything
	}
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->meals_mutex[i], NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->meals_mutex[j++]);
			free(arrays->meals_mutex);
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			pthread_mutex_destroy(&arrays->start_mutex);
			pthread_mutex_destroy(&arrays->done_mutex);
			ft_destroy_array_mutexes(arrays->forks);
			free(arrays->forks);
			exit (1);
		}
		i++;
	}
	return (0);//?
}

static int	ft_last_meal_mutex(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	arrays->last_meal_mutex = malloc((args->nb_philo) * sizeof(pthread_mutex_t));
	if (arrays->last_meal_mutex == NULL)
	{
		ft_puterror("Allocation error"); //what else should I clean here
		exit (1);//clean everything
	}
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->last_meal_mutex[i], NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->last_meal_mutex[j++]);
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			pthread_mutex_destroy(&arrays->start_mutex);
			pthread_mutex_destroy(&arrays->done_mutex);
			ft_destroy_array_mutexes(arrays->forks);
			ft_destroy_array_mutexes(arrays->meals_mutex);
			free(arrays->forks);
			free(arrays->meals_mutex);
			exit (1);
		}
		i++;
	}
	return (0);//?
}

static int  ft_init_threads_and_meals(t_args *args, t_arrays *arrays)
{
    int i;
    
    i = 0;
    arrays->threads = malloc((args->nb_philo) * sizeof(pthread_t));
	if (arrays->threads == NULL)
	{
		ft_puterror("Allocation error");
		ft_destroy_mutexes();
		free(arrays->forks);
		free(arrays->meals_mutex);
		exit (1);
	}
   	arrays->meals = malloc((args->nb_philo) * sizeof(int));
   	if (arrays->meals == NULL)
	{
		ft_puterror("Allocation error");
		ft_destroy_mutexes();
		free(arrays->forks);
		free(arrays->threads);
		free(arrays->meals_mutex);
		exit (1);
	}
    while (i < args->nb_philo)
		arrays->meals[i++] = 0;
    return (0);//?
}

static int  ft_init_thread_ids(t_args *args, t_arrays *arrays)
{
    int	i;

    i = 0;
	arrays->thread_ids = malloc((args->nb_philo) * sizeof(int));
	if (arrays->thread_ids == NULL)
	{
		ft_puterror("Allocation error");
		ft_destroy_mutexes();
		free(arrays->forks);
		free(arrays->threads);
        free(arrays->meals);
		free(arrays->meals_mutex);
		exit (1);
	}
	while (i < args->nb_philo)
	{
		arrays->thread_ids[i] = i;
		i++;
	}
    return (0);//?
}

static int  ft_init_last_meal(t_args *args, t_arrays *arrays)
{
    arrays->last_meal = malloc((args->nb_philo) * sizeof(struct timeval));
	if (arrays->last_meal == NULL)
	{
		ft_puterror("Allocation error");
		ft_destroy_mutexes();
		free(arrays->forks);
		free(arrays->threads);
        free(arrays->meals);
		free(arrays->meals_mutex);
		free(arrays->thread_ids);
		exit (1);
	}
    return (0);
}

static int	ft_thread(t_args *args, t_arrays *arrays)
{
	int i;
    int j;
    
	i = 0;
    ft_init_threads_and_meals(args, arrays);
    ft_init_thread_ids(args, arrays);
	ft_init_last_meal(args, arrays);
	args->can_start = false;
	while (i < args->nb_philo)
	{
		if (pthread_create(&arrays->threads[i], NULL, ft_start_routine, &arrays->thread_ids[i]) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
			pthread_join(arrays->threads[j++], NULL);
			exit (ft_free_destroy_return(1, false));
		}
		i++;
	}
	i = 0;
	gettimeofday(&args->start_time, NULL);
	while (i < args->nb_philo)
		arrays->last_meal[i++] = args->start_time;
	pthread_mutex_lock(&arrays->start_mutex);
	args->can_start = true;
	pthread_mutex_unlock(&arrays->start_mutex);
	if (pthread_create(&arrays->monitor, NULL, ft_monitor, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		exit (ft_free_destroy_return(1, false));//correct this
	}
	return (0);//?
}

int	ft_mutex_and_thread(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

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
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->forks[j++]);
			free(arrays->forks);
			exit (1);
		}
		i++;
	}
    pthread_mutex_init(&arrays->print_mutex, NULL);//add error check for these 3
    pthread_mutex_init(&arrays->death_mutex, NULL);
    pthread_mutex_init(&arrays->start_mutex, NULL);
    pthread_mutex_init(&arrays->done_mutex, NULL);
	ft_meals_mutex(args, arrays);
	ft_last_meal_mutex(args, arrays);
	ft_thread(args, arrays);
	return (0);//?
}
