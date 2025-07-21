/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:33:32 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 14:45:15 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//START HERE - SLEEP AND THINK
void	ft_sleep_and_think(t_arrays *arrays, t_args *args, int thread_id)
{  
   	ft_print(arrays, args, thread_id, "is sleeping\n");
	usleep(args->sleep_time * 1000);
    ft_print(arrays, args, thread_id, "is thinking\n");
}