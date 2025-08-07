/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 17:52:45 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unlink_semaphores(void)
{
	int			i;
	t_args		*args;
	char		*name;
	char		*id;

	args = ft_args();
	i = 0;
	while (i < args->nb_philo)
	{
		id = ft_itoa(i);
		name = ft_strjoin("/turn_id_", id);
		sem_unlink(name);
		free(name);
		name = ft_strjoin("/waiter_id_", id);
		sem_unlink(name);
		free(name);
		free(id);
		i++;
	}
	sem_unlink("/print_sem");
}

int	ft_close_philos(int ret) //only for children!!!!!!
{
	t_philo		*philo;
	t_args		*args;

	philo = ft_create_philo();
	args = ft_args();
	sem_close(philo->turn_sem);
	sem_close(args->print_sem);
	sem_close(philo->waiter_sem);
	pthread_mutex_destroy(&philo->monitor_mutex);
	pthread_mutex_destroy(&philo->death_mutex);
	//pthread_join(philo->monitor, NULL);
	return (ret);
}

void	ft_close_parent(void) // only parent!!!!!!
{
	int i;
	t_args		*args;

	args = ft_args();
	i = 0;
	sem_close(args->print_sem);
	while (i < args->nb_philo)
	{
		sem_close(args->all_philo_sems[i]);
		sem_close(args->all_waiter_sems[i]);
		free(args->waiter_sems_names[i]);
		free(args->philo_sems_names[i]);
		i++;
	}
	free(args->waiters);
	free(args->w_threads);
	free(args->all_philo_sems);
	free(args->all_waiter_sems);
	free(args->waiter_sems_names);
	free(args->philo_sems_names);
}


int	ft_close_waiters(int id)
{
	t_philo		*philo;
	t_args		*args;

	philo = ft_create_philo();
	args = ft_args();
	sem_close(args->waiters[id].philo_sem);
	sem_close(args->print_sem);
	sem_close(args->waiters[id].left_sem);
	sem_close(args->waiters[id].my_sem);
	return (0);
}