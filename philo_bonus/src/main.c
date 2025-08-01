/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:52 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/01 14:22:08 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_args	*ft_args(void)
{
	static t_args	args;

	return (&args);
}

t_arrays	*ft_arrays(void)
{
	static t_arrays	arrays;

	return (&arrays);
}

int	main(int argc, char **argv)
{
	t_args		*args;
	t_arrays	*arrays;

	args = ft_args();
	arrays = ft_arrays();
	args->should_eat = -1;
	ft_parse_args(args, argc, argv);
	ft_semaphores(arrays);
	ft_forks(args, arrays);
	sem_close(arrays->print_sem);
	sem_close(arrays->forks);
	ft_unlink_semaphores();
	return (0);
}
