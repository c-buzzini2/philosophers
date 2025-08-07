/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:52 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 17:53:30 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_args	*ft_args(void)
{
	static t_args	args;

	return (&args);
}

int	main(int argc, char **argv)
{
	t_args		*args;

	printf("Hello!");
	args = ft_args();
	args->should_eat = -1;
	ft_parse_args(args, argc, argv);
	ft_unlink_semaphores();
	ft_print_semaphore(args);
	ft_forks(args);
	ft_unlink_semaphores();
	return (0);
}
