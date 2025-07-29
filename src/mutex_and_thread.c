/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 13:39:56 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_forks_and_meals(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->philos[i].fork, NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->philos[j++].fork);
			i = 0;
			while (i < args->nb_philo)
				pthread_mutex_destroy(&arrays->philos[i++].mutex);
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			free(arrays->philos);
			exit (1);
		}
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
		arrays->philos[i++].meals = 0;
	return (0);//?
}

static void	ft_init_turns_mutex(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->philos[i].turn_mutex, NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->philos[j++].turn_mutex);
			i = 0;
			while (i < args->nb_philo)
			{
				pthread_mutex_destroy(&arrays->philos[i].mutex);
				pthread_mutex_destroy(&arrays->philos[i++].fork);
			}
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			free(arrays->philos);
			exit (1);
		}
		i++;
	}
}

static int	ft_thread(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	gettimeofday(&args->start_time, NULL);
	while (i < args->nb_philo)
	{
		if (pthread_create(&arrays->philos[i].thread, NULL, ft_start_routine,
				&arrays->philos[i].id) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_join(arrays->philos[j++].thread, NULL);
			ft_destroy_mutexes();
			free(arrays->philos);
			exit (1);
		}
		i++;
	}
	if (pthread_create(&arrays->monitor, NULL, ft_monitor, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		ft_join_philos();
		ft_destroy_mutexes();
		free(arrays->philos);
		exit (1);
	}
	return (0);
}

int	ft_mutex_and_thread(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->philos[i].mutex, NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->philos[j++].mutex);
			free(arrays->philos);
			exit (1);
		}
		i++;
	}
	pthread_mutex_init(&arrays->print_mutex, NULL);//add error check for these 2
	pthread_mutex_init(&arrays->death_mutex, NULL);
	ft_init_forks_and_meals(args, arrays);
	ft_init_turns_mutex(args, arrays);
	ft_thread(args, arrays);
	return (0);
}
