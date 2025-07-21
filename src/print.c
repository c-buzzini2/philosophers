/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 12:35:38 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print(t_arrays *arrays, t_args *args, int thread_id, char *action)
{
    struct timeval current;
    double timestamp;

    pthread_mutex_lock(&arrays->print_mutex);
    gettimeofday(&current, NULL);
    timestamp = ft_time_ms(args->start_time, current);
    printf("%.0f: P%d %s", timestamp, thread_id + 1, action);
	printf("        (Thread %d, meal %d)\n", thread_id, arrays->meals[thread_id]);//delete!!
    pthread_mutex_unlock(&arrays->print_mutex);
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
