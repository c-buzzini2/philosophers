/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:30:37 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/29 16:01:52 by cbuzzini         ###   ########.fr       */
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
# include <string.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				meals;
	long			last_meal;
	pthread_mutex_t	mutex;
	pthread_mutex_t	turn_mutex;
	bool			own_turn;
}	t_philo;

typedef struct s_args
{
	int				nb_philo;
	int				die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				should_eat;
	struct timeval	start_time;
	bool			death;
	bool			can_start;
	int				done_eating;
}	t_args;

typedef struct s_arrays
{
	pthread_t		monitor;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_arrays;

int				ft_isdigit(int c);
unsigned int	ft_atoi(const char *nptr);
int				ft_parse_args(t_args *args, int argc, char **argv);
void			ft_allocate_philos(t_arrays *arrays, t_args *args);
void			ft_puterror(char *s);
t_arrays		*ft_arrays(void);
t_args			*ft_args(void);
int				ft_free_destroy_return(int ret);
void			ft_destroy_mutexes(void);
void			ft_mutexes(t_args *args, t_arrays *arrays);
void			ft_threads(t_args *args, t_arrays *arrays);
void			*ft_start_routine(void *arg);
int				ft_prepare_to_eat(t_arrays *arrays, t_args *args, int id,
					int l_philo);
long			ft_timestamp_ms(void);
int				ft_print(t_arrays *arrays, int id, char *str);
int				ft_sleep_and_think(t_arrays *arrays, t_args *args, int id);
int				ft_check_starvation(t_arrays *arrays, t_args *args);
int				ft_check_death_flag(void);
void			*ft_monitor(void *arg);
void			ft_join_philos(void);

#endif