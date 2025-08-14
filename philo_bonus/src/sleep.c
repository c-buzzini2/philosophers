/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:33:32 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/14 11:00:16 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_sleep_and_think(t_philo *philo, t_args *args)
{
	int				ret;
	long			sleep_start;

	ret = 0;
	ft_print(philo, "is sleeping\n");
	sleep_start = ft_timestamp_ms();
	while (ft_timestamp_ms() - sleep_start < args->sleep_time)
	{
		if (args->sleep_time - (ft_timestamp_ms() - sleep_start) < 5)
		{
			usleep((args->sleep_time
					- (ft_timestamp_ms() - sleep_start)) * 1000);
			break ;
		}
		else
			usleep(5000);
	}
	if (ft_print(philo, "is thinking\n") == 2)
		ret = 2;
	return (ret);
}
