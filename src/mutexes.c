/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 16:00:29 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			free(arrays->philos);
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
			free(arrays->philos);
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
		free(arrays->philos);
		exit (1);
	}
	if (pthread_mutex_init(&arrays->death_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		pthread_mutex_destroy(&arrays->print_mutex);
		free(arrays->philos);
		exit (1);
	}
	ft_init_philos_mutex(args, arrays);
	ft_init_forks_and_meals(args, arrays);
	ft_init_turns_mutex(args, arrays);
}
