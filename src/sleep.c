/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:33:32 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/24 19:11:28 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//START HERE - adjust code, than print, then monitor
//are there exits left, and are they ok?
int	ft_sleep_and_think(t_arrays *arrays, t_args *args, int thread_id)
{  
	useconds_t		slept;
	int				ret;

	ret = 0;
	slept = 0;
   	ft_print(arrays, args, thread_id, "is sleeping\n");
	while (slept / 1000 < args->sleep_time)
	{
		if (ft_check_death_flag() == 2)
		{
			ret = 2;
			break ;
		}
		if (args->sleep_time * 1000 - slept < 5000)
		{
			usleep(args->sleep_time * 1000 - slept);
			break ;
		}
		else
			usleep(5000);
		slept += 5000;
	}
    if (ft_print(arrays, args, thread_id, "is thinking\n") == 2)
		ret = 2;
	//usleep(500);//precisa?
	return (ret);
}