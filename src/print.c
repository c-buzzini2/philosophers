/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/25 15:04:55 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death_flag(void)
{
	t_args		*args;
	t_arrays	*arrays;

	args = ft_args();
	arrays = ft_arrays();
	pthread_mutex_lock(&arrays->death_mutex);
	if (args->death == true)
	{
		pthread_mutex_unlock(&arrays->death_mutex);
		return (2);
	}
	pthread_mutex_unlock(&arrays->death_mutex);
	return (0);
}

int ft_print(t_arrays *arrays, int id, char *action)
{
    long timestamp;

    timestamp = ft_timestamp_ms();
    if (ft_check_death_flag() == 2)
		return (2);
    pthread_mutex_lock(&arrays->print_mutex);
    printf("%ld: P%d %s", timestamp, id + 1, action);
    pthread_mutex_unlock(&arrays->print_mutex);
	return (0);
}

static void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	write(fd, &c, 1);
}

void	ft_puterror(char *s)
{
	int	n;

	n = 0;
	if (!s)
		return ;
	while (s[n] > 0)
	{
		ft_putchar_fd(s[n], 2);
		n++;
	}
	ft_putchar_fd('\n', 2);
}
