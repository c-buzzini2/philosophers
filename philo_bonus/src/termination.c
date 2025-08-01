/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:36:47 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/01 16:35:09 by cbuzzini         ###   ########.fr       */
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
	sem_unlink("/forks");
}

int	ft_close_semaphores(int ret) //only for children!!!!!!
{
	t_arrays	*arrays;
	t_philo		*philo;

	philo = ft_create_philo();
	arrays = ft_arrays();
	sem_close(philo->turn_sem);
	sem_close(philo->left_sem);
	sem_close(arrays->print_sem);
	sem_close(arrays->forks);
	return (ret);
}
