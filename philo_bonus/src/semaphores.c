/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 15:10:17 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_open_turn_sems(t_philo *philo)
{
	char	*id;

	id = ft_itoa(philo->id);
	ft_strlcpy(philo->turn_name, "/turn_id_", 20);
	ft_strlcat(philo->turn_name, id, 20);
	free(id);
	if (philo->id % 2 != 0)
		philo->turn_sem = sem_open(philo->turn_name, 0);
	else
		philo->turn_sem = sem_open(philo->turn_name, 0);
	if (philo->turn_sem == SEM_FAILED)
	{
		perror("sem_open failed\n");
		exit(1); //graceful termination
	}
}

void	ft_print_semaphore(t_args *args)
{
	args->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0600, 1);
	if (args->print_sem == SEM_FAILED)
	{
		ft_puterror("sem_open failed\n");
		exit(1);
	}
	args->waiter_sem = sem_open("/waiter_sem", O_CREAT | O_EXCL, 0600, 0);
	if (args->waiter_sem == SEM_FAILED)
	{
		ft_puterror("sem_open failed\n");
		sem_close(args->print_sem);
		exit(1);
	}
}
