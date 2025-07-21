/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:30:37 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/21 13:22:02 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_args
{
	int	nb_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	should_eat;
	struct timeval start_time;
}	t_args;

typedef struct s_arrays
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	int				*thread_ids;
	int				*meals;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	print_mutex;
}	t_arrays;

int 		ft_parse_args(t_args *args, int argc, char **argv);
void		ft_puterror(char *s);
t_arrays	*ft_arrays(void);
t_args		*ft_args(void);
int			ft_free_destroy_return(int ret, bool join_threads);
void		ft_destroy_mutexes(void);
int			ft_mutex_and_thread(t_args *args, t_arrays *arrays);
void 		*ft_start_routine(void *arg); 
void		ft_prepare_to_eat(t_arrays *arrays, int thread_id, int l_philo);
double 		ft_time_ms(struct timeval start, struct timeval end);
void 		ft_print(t_arrays *arrays, t_args *args, int thread_id, char *str);
void    	ft_destroy_array_mutexes(pthread_mutex_t *arr);



//void    ft_free_arrays(void **array);





#endif