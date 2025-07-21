/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:33:32 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 15:54:29 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//START HERE - ADD DEATH CHECK EVERY xMS to make sure the message doesnt take too long
//also check if another philosopher has died 
//is it a good option to return from the print function instead, and just exit at the end of
//the "eat" or "sleep and think" functions?
//what is the idea of having a monitoring thread?
//clean all the returns in the process, so that we can return everything
//remember that exiting influences all threads
void	ft_sleep_and_think(t_arrays *arrays, t_args *args, int thread_id)
{  
   	ft_print(arrays, args, thread_id, "is sleeping\n");
	usleep(args->sleep_time * 1000);
    ft_print(arrays, args, thread_id, "is thinking\n");
}