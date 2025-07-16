/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:30:37 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/16 13:55:20 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_args
{
	int	nb_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	should_eat;
}	t_args;

typedef struct s_arrays
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
}	t_arrays;

int 	ft_parse_args(t_args *args, int argc, char **argv);
void	ft_puterror(char *s);
t_arrays	*ft_arrays(void);
t_args	*ft_args(void);





#endif