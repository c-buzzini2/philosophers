/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:52 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/22 16:33:38 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*ft_args(void)
{
	static	t_args args;
	
	return (&args);
}

t_arrays	*ft_arrays(void)
{
	static	t_arrays arrays;
	
	return (&arrays);
}

int main (int argc, char **argv)
{
	t_args *args;
	t_arrays *arrays;
	//int		i;

	//i = 0;
	args = ft_args();
	arrays = ft_arrays();
	args->should_eat = -1;
	args->death = false;
	ft_parse_args(args, argc, argv);
    ft_mutex_and_thread(args, arrays);
	return(ft_free_destroy_return(0, true)); // when the threads exit on their own, is it a problem to join them again in the end?
}