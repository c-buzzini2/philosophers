/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/14 11:01:07 by cbuzzini         ###   ########.fr       */
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
		free(id);
		i++;
	}
	sem_unlink("/print_sem");
	sem_unlink("/waiter_sem");
}

int	ft_close_semaphores(int ret) //only for children
{
	t_philo		*philo;
	t_args		*args;

	philo = ft_create_philo();
	args = ft_args();
	if (ret == 0)
		pthread_join(philo->monitor, NULL);
	sem_close(args->print_sem);
	sem_close(args->waiter_sem);
	pthread_mutex_destroy(&philo->monitor_mutex);
	pthread_mutex_destroy(&philo->death_mutex);
	return (ret);
}

void	ft_close_arr_sems(void) // only parent
{
	int		i;
	t_args	*args;

	args = ft_args();
	i = 0;
	while (i < args->nb_philo)
	{
		sem_close(args->waiter.philo_sems[i]);
		free(args->waiter.sem_names[i]);
		i++;
	}
	free(args->waiter.philo_sems);
	free(args->waiter.sem_names);
}
