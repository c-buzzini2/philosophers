/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 12:56:34 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_print(t_arrays *arrays, int id, char *action)
{
	long	timestamp;

	timestamp = ft_timestamp_ms();
	if (ft_check_death_flag() == 2)
		return (2);
	sem_wait(arrays->print_sem);
	printf("%ld: P%d %s", timestamp, id + 1, action);
	sem_post(arrays->print_sem);
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
