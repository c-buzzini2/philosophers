/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:30:37 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/04 12:14:15 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int		id;
	int		meals;
	long	last_meal;
	sem_t	*turn_sem;
	char	turn_name[20];
	char	l_name[20];
	sem_t	*left_sem;
	pthread_t		monitor;
	pthread_mutex_t	monitor_mutex;
	bool	death;
	pthread_mutex_t	death_mutex;
}	t_philo;

typedef struct s_pids
{
	int		pid;
	bool	exited;	
}	t_pids;

typedef struct s_args
{
	int				nb_philo;
	int				die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				should_eat;
	struct timeval	start_time;
}	t_args;

typedef struct s_arrays
{
	sem_t	*print_sem;
	sem_t	*forks;	
}	t_arrays;

int				ft_isdigit(int c);
unsigned int	ft_atoi(const char *nptr);
int				ft_parse_args(t_args *args, int argc, char **argv);
t_philo			*ft_create_philo(void);
void			ft_puterror(char *s);
t_arrays		*ft_arrays(void);
t_args			*ft_args(void);
int				ft_close_semaphores(int ret);
void			ft_unlink_semaphores(void);
void			ft_semaphores(t_arrays *arrays);
void			ft_open_turn_sems(t_philo *philo, t_args *args);
unsigned int	ft_strlcpy(char *dst, const char *src, size_t size);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *s);
int				ft_forks(t_args *args, t_arrays *arrays);
int				ft_start_routine(t_philo *philo);
int				ft_eat(t_philo *philo);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
int				ft_grab_forks(t_philo *philo);
long			ft_timestamp_ms(void);
int				ft_print(t_philo *philo, char *action);
int				ft_sleep_and_think(t_philo *philo, t_args *args);
void			*ft_monitor(void *arg);
void			ft_free_array(int *pids, t_args *args);
int			ft_mutex_and_thread(t_philo *philo);
int				ft_check_death_flag(void);


#endif