/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/23 12:19:58 by cbuzzini         ###   ########.fr       */
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

int ft_print(t_arrays *arrays, t_args *args, int thread_id, char *action)
{
    struct timeval current;
    double timestamp;

	if (ft_check_death_flag() == 2)
		return (2);
    pthread_mutex_lock(&arrays->print_mutex);
    gettimeofday(&current, NULL);
	if (ft_check_starvation(arrays, args, thread_id) == 2)
	{
		pthread_mutex_unlock(&arrays->print_mutex);
		return (2);
	}
    timestamp = ft_time_ms(args->start_time, current);
    printf("%.0f: P%d %s", timestamp, thread_id + 1, action);
	printf("        (Thread %d, meal %d)\n", thread_id, arrays->meals[thread_id]);//delete!!
    pthread_mutex_unlock(&arrays->print_mutex);
	return (0);
}

static void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	if (write(fd, &c, 1) == -1)
		exit(-1);//graceful termination!!!
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
