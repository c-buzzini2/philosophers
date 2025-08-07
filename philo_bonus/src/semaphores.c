/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 15:53:18 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_open_philo_sems(t_philo *philo)
{
	char	*id;
	t_args	*args;

	args = ft_args();
	id = ft_itoa(philo->id);
	ft_strlcpy(philo->turn_name, "/turn_id_", 20);
	ft_strlcat(philo->turn_name, id, 20);
	ft_strlcpy(philo->waiter_name, "/waiter_id_", 22);
	ft_strlcat(philo->waiter_name, id, 22);
	free(id);
	philo->turn_sem = sem_open(philo->turn_name, 0);
	philo->waiter_sem = sem_open(philo->waiter_name, 0);
	if (philo->turn_sem == SEM_FAILED || philo->waiter_sem == SEM_FAILED) 
	{
		perror("sem_open failed\n");
		exit(1); //graceful termination
	}
}

void	ft_open_waiter_sems(int i)
{
	char	*id;
	t_args	*args;
	int		left;

	args = ft_args();
	left = i - 1;
	if (left == -1)
		left = args->nb_philo - 1;
	id = ft_itoa(i);
	ft_strlcpy(args->waiters[i].philo_name, "/turn_id_", 20);
	ft_strlcat(args->waiters[i].philo_name, id, 20);
	ft_strlcpy(args->waiters[i].my_name, "/waiter_id_", 22);
	ft_strlcat(args->waiters[i].my_name, id, 22);
	free(id);
	id = ft_itoa(left);
	ft_strlcpy(args->waiters[i].left_name, "/turn_id_", 20);
	ft_strlcat(args->waiters[i].left_name, id, 20);
	free(id);
	args->waiters[i].philo_sem = sem_open(args->waiters[i].philo_name, 0);
	args->waiters[i].my_sem = sem_open(args->waiters[i].my_name, 0);
	args->waiters[i].left_sem = sem_open(args->waiters[i].left_name, 0);
	if (args->waiters[i].left_sem == SEM_FAILED 
		|| args->waiters[i].my_sem == SEM_FAILED
		|| args->waiters[i].philo_sem == SEM_FAILED) 
	{
		perror("sem_open failed\n");
		exit(1); //graceful termination
	}
}

void	ft_print_semaphore(t_args *args)
{
	//sem_unlink("/print_sem");
	args->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0600, 1);
	if (args->print_sem == SEM_FAILED) 
	{
		ft_puterror("sem_open failed\n");
		exit(1);
	}
	//sem_unlink("/waiter_sem");
/* 	args->waiter_sem = sem_open("/waiter_sem", O_CREAT | O_EXCL, 0600, 0);
	if (args->waiter_sem == SEM_FAILED) 
	{
		ft_puterror("sem_open failed\n");
		sem_close(args->print_sem);
		exit(1);
	} */
}
