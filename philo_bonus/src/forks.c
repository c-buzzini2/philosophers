/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 16:33:40 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_create_philo(void)
{
	static t_philo	philo;

	return (&philo);
}

t_pids	*ft_allocate_pids(t_args *args)
{
	t_pids	*pids;

	pids = malloc(args->nb_philo * sizeof(t_pids));
	if (pids == NULL)
	{
		perror("Error in allocation");
		sem_close(args->print_sem);
		ft_close_arr_sems();
		ft_unlink_semaphores();
		exit(1);
	}
	return (pids);
}

void	ft_fork_error(t_args *args)
{
	perror("Error in the fork");
	sem_close(args->print_sem);
	ft_unlink_semaphores();
	exit(1);
}

int	ft_forks(t_args *args, int forks, t_pids *pids, int i)
{
	t_philo	*philo;
	int		id;

	id = fork();
	if (id == -1)
		ft_fork_error(args);
	if (id == 0)
	{
		free(pids);
		ft_close_arr_sems();
		philo = ft_create_philo();
		philo->id = forks;
		if (ft_mutex_and_thread(philo) == 1)
			return (3);
		ft_open_turn_sems(philo);
		ft_start_routine(philo);
	}
	else
	{
		pids[i].pid = id;
		pids[i].exited = false;
	}
	return (0);
}

int	ft_prepare_to_fork(t_args *args)
{
	int		forks;
	t_pids	*pids;
	int		i;		

	i = 0;
	forks = 0;
	pids = ft_allocate_pids(args);
	if (ft_allocate_waiter_arrays(args) == 1)
	{
		free(pids);
		ft_close_arr_sems();
		return (1);
	}
	gettimeofday(&args->start_time, NULL);
	while (forks < args->nb_philo)
	{
		if (ft_forks(args, forks, pids, i) == 3)
			return (3);
		forks++;
		i++;
	}
	if (ft_waiter(args) == 1)
		return (ft_waiter_error(args, pids));
	return (ft_parent(args, pids));
}
