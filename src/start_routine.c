/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 13:35:48 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_timestamp_ms(void)
{
	t_args			*args;
	struct timeval	current;

	args = ft_args();
	gettimeofday(&current, NULL);
	return ((current.tv_sec - args->start_time.tv_sec) * 1000
		+ (current.tv_usec - args->start_time.tv_usec) / 1000.0);
}

void	*ft_start_routine(void *arg)
{
	int			id;
	t_arrays	*arrays;
	int			l_philo;
	t_args		*args;

	id = *(int *)arg;
	arrays = ft_arrays();
	args = ft_args();
	l_philo = id - 1;
	if (l_philo == -1)
	{
		l_philo = args->nb_philo - 1;
	}
	if (args->should_eat == 0)
		return (NULL);
	while (1)
	{
		if (ft_prepare_to_eat(arrays, args, id, l_philo) == 2
			|| arrays->philos[id].meals == args->should_eat
			|| ft_check_death_flag() == 2
			|| ft_sleep_and_think(arrays, args, id) == 2
			|| ft_check_death_flag() == 2)
			break ;
	}
	return (NULL);
}
