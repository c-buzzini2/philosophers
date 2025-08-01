/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/01 15:20:47 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_open_turn_sems(t_philo *philo, t_args *args)
{
	char	*id;
	int		l_philo;
	
	id = ft_itoa(philo->id);
	ft_strlcpy(philo->turn_name, "/turn_id_", 20);
	ft_strlcat(philo->turn_name, id, 20);
	free(id);
	l_philo = philo->id - 1;
	if (l_philo == -1)
		l_philo = args->nb_philo - 1;
	id = ft_itoa(l_philo);
	ft_strlcpy(philo->l_name, "/turn_id_", 20);
	ft_strlcat(philo->l_name, id, 20);
	free(id);
	if (philo->id % 2 != 0)
		philo->turn_sem = sem_open(philo->turn_name, O_CREAT, 0600, 1);
	else
		philo->turn_sem = sem_open(philo->turn_name, O_CREAT, 0600, 0);
	while (1)
	{
		philo->left_sem = sem_open(philo->l_name, 0);
		if (philo->left_sem != SEM_FAILED)
			break;
	}
}

void	ft_semaphores(t_arrays *arrays)
{
	int		i;
	t_args	*args;
	char	*name;
	char	*id;

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
	arrays->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0600, 1);
	if (arrays->print_sem == SEM_FAILED) 
	{
		ft_puterror("sem_open failed\n");
		exit(1);
	}
	sem_unlink("/forks");
	arrays->forks = sem_open("/forks", O_CREAT | O_EXCL, 0600, 1);
	if (arrays->forks == SEM_FAILED) 
	{
		ft_puterror("sem_open failed\n");
		sem_close(arrays->print_sem);
		sem_unlink("/print_sem");
		exit(1);
	}
}
