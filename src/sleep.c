/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:33:32 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/25 15:12:31 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//START HERE
//are there exits left, and are they ok?
int	ft_sleep_and_think(t_arrays *arrays, t_args *args, int id)
{  
	int				ret;
	long			sleep_start;

	ret = 0;
   	ft_print(arrays, id, "is sleeping\n");
	sleep_start = ft_timestamp_ms();
	while (ft_timestamp_ms() - sleep_start < args->sleep_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->sleep_time - (ft_timestamp_ms() - sleep_start) < 5)
		{
			usleep((args->sleep_time - (ft_timestamp_ms() - sleep_start)) * 1000);
			break ;
		}
		else
			usleep(5000);
	}
    if (ft_print(arrays, id, "is thinking\n") == 2)
		ret = 2;
	return (ret);
}
