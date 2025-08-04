/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/04 14:50:26 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_waiters_mutex(t_args *args, t_arrays *arrays)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&arrays->waiters[i].turn_mutex, NULL) != 0)
		{
			ft_puterror("Could not initialize mutex");
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&arrays->waiters[j++].turn_mutex);
			i = 0;
			while (i < args->nb_philo)
			{
				pthread_mutex_destroy(&arrays->philos[i].mutex);
				pthread_mutex_destroy(&arrays->philos[i++].fork);
			}
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			ft_free_arrays();
			exit (1);
		}
		i++;
	}
}

static void	ft_init_forks_and_meals(t_args *args, t_arrays *arrays)
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
			ft_free_arrays();
			exit (1);
		}
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
		arrays->philos[i++].meals = 0;
}

void	ft_init_philos_mutex(t_args *args, t_arrays *arrays)
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
			pthread_mutex_destroy(&arrays->print_mutex);
			pthread_mutex_destroy(&arrays->death_mutex);
			ft_free_arrays();
			exit (1);
		}
		i++;
	}
}

void	ft_mutexes(t_args *args, t_arrays *arrays)
{
	if (pthread_mutex_init(&arrays->print_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		ft_free_arrays();
		exit (1);
	}
	if (pthread_mutex_init(&arrays->death_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		pthread_mutex_destroy(&arrays->print_mutex);
		ft_free_arrays();
		exit (1);
	}
	ft_init_philos_mutex(args, arrays);
	ft_init_forks_and_meals(args, arrays);
	ft_init_waiters_mutex(args, arrays);
}
