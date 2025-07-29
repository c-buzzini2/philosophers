/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:52 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 15:53:41 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	args->death = false;
	ft_parse_args(args, argc, argv);
	ft_allocate_philos(arrays, args);
	ft_mutexes(args, arrays);
	ft_threads(args, arrays);
	return (ft_free_destroy_return(0));
}
