/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:30:37 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 15:32:52 by cbuzzini         ###   ########.fr       */
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

typedef struct s_philo
{
	int		id;
	int		meals;
	long	last_meal;
	sem_t	turn_sem;
	char	*turn_name[20];
	char	*l_name[20];
	sem_t	left_sem;
}	t_philo;

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
	sem_t	print_sem;
	sem_t	forks;	
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
void			ft_semaphores(t_args *args, t_arrays *arrays);
static void		ft_open_turn_sems(t_philo *philo, t_args *args);
unsigned int	ft_strlcpy(char *dst, const char *src, size_t size);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
int				ft_forks(t_args *args);
void			*ft_start_routine(t_philo *philo);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
// int				ft_prepare_to_eat(t_arrays *arrays, int id,	int l_philo);
// int				ft_grab_forks(int first, int second, int id, int l_philo);
long			ft_timestamp_ms(void);
// int				ft_print(t_arrays *arrays, int id, char *str);
// int				ft_sleep_and_think(t_arrays *arrays, t_args *args, int id);
// int				ft_check_starvation(t_arrays *arrays, t_args *args);
// int				ft_check_death_flag(void);
// void			*ft_monitor(void *arg);
// void			ft_join_philos(void);

#endif