/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_waiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 17:11:57 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error_sem_names(t_args *args, int i)
{
	int	j;

	ft_puterror("Allocation error");
	j = 0;
	while (j < i)
		free(args->waiter.sem_names[j++]);
	sem_close(args->print_sem);
	free(args->waiter.philo_sems);
	free(args->waiter.sem_names);
	return (1);
}

int	ft_allocate_sem_names(t_args *args)
{
	int		i;
	char	*id;

	i = 0;
	while (i < args->nb_philo)
	{
		args->waiter.sem_names[i] = malloc(20 * sizeof(char));
		if (args->waiter.sem_names[i] == NULL)
			return (ft_error_sem_names(args, i));
		id = ft_itoa(i);
		ft_strlcpy(args->waiter.sem_names[i], "/turn_id_", 20);
		ft_strlcat(args->waiter.sem_names[i], id, 20);
		free(id);
		i++;
	}
	return (0);
}

int	ft_open_waiter_sems(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (i % 2 != 0)
			args->waiter.philo_sems[i] = sem_open(args->waiter.sem_names[i],
					O_CREAT, 0600, 1);
		else
			args->waiter.philo_sems[i] = sem_open(args->waiter.sem_names[i],
					O_CREAT, 0600, 0);
		if (args->waiter.philo_sems[i] == SEM_FAILED)
		{
			ft_puterror("sem_open failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_allocate_waiter_arrays(t_args *args)
{
	args->waiter.philo_sems = malloc((args->nb_philo) * sizeof(sem_t *));
	if (args->waiter.philo_sems == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		return (1);
	}
	memset(args->waiter.philo_sems, 0, (args->nb_philo) * sizeof(sem_t *));
	args->waiter.sem_names = malloc((args->nb_philo) * sizeof(char *));
	if (args->waiter.sem_names == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiter.philo_sems);
		return (1);
	}
	ft_allocate_sem_names(args);
	ft_open_waiter_sems(args);
	return (0);
}
